#include <unistd.h> // for vfork()
#include <signal.h> // for kill()
#include <iostream>

#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/exception/detail/exception_ptr_base.hpp>
#include <boost/thread.hpp>

#include "sandbox.hpp"
#include "protein.hpp"
#include "exception.hpp"
#include "vm.hpp"

namespace bip = ::boost::interprocess;

Sandbox::Sandbox() :
	inqueue(bip::open_or_create, "sandbox_inqueue", 1, sizeof(Message)),
	outqueue(bip::open_or_create, "sandbox_outqueue", 1, sizeof(Message))
{
	do_fork();
}

Sandbox::~Sandbox() {
	if(pid)
		kill(pid, SIGKILL);
}

void Sandbox::run_child() {
	while(1) {
		byte buffer[PROTEIN_MAX_LENGTH];
		std::size_t buffer_size = sizeof(buffer);
		std::size_t recvd_size = 0;
		unsigned int priority = 0;
		inqueue.receive((void*)buffer, buffer_size, recvd_size, priority);
		ByteArray ba(buffer, recvd_size);
		signed long ttl_delta = vm_tester(ba, this);
		outqueue.send(&ttl_delta, sizeof(ttl_delta), 1);
	}
}

void Sandbox::do_fork() {
	pid = fork();
	if(pid > 0)
		run_child();
	else if (pid < 0) {
		std::cerr << "Failed to fork Sandbox" << std::endl;
		exit(1);
	}
}

signed long Sandbox::run(const ByteArray &dna) {
	using boost::posix_time::ptime;
	using boost::posix_time::seconds;
	inqueue.send(&dna[0], dna.size(), 1);
	signed long ttl_delta = 0;
	std::size_t recvd = 0;
	unsigned int priority = 0;
	ptime timeout = boost::get_system_time() + seconds(SANDBOX_TIMEOUT);
	if(outqueue.timed_receive((void*)&ttl_delta, (std::size_t)sizeof(ttl_delta), recvd, priority, timeout)) {
		return ttl_delta;
	}
	else {
		// failed, kill and restart process
		kill(pid, SIGKILL);
		pid = 0;
		do_fork();
		throw timeout_error();
	}
}

