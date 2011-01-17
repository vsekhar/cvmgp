#include <unistd.h> // for vfork()
#include <signal.h> // for kill()

#include <boost/interprocess/ipc/message_queue.hpp>

#include "sandbox.hpp"
#include "protein.hpp"
#include "exception.hpp"
#include "vm.hpp"


Sandbox::Sandbox() {
	namespace bip = ::boost::interprocess;
	inqueue = bip::message_queue (open_or_create, 
								"sandbox_inqueue",
								1,
								PROTEIN_MAX_LENGTH);
	outqueue = bip::message_queue (open_or_create,
								"sandbox_outqueue",
								1,
								sizeof(signed long));
	do_fork(true);
}

Sandbox::~Sandbox() {
	if(pid)
		kill(pid, SIGKILL);
}

void setup_parent() {}
void setup_child() {
	while(1) {
		byte buffer[PROTEIN_MAX_LENGTH];
		std::size_t recvd_size = 0;
		unsigned int priority = 0;
		inqueue.receive(buffer, sizeof(buffer), &recvd_size, &priority);
		//signed long ttl_delta = vm_run(buffer, state?);
		outqueue.send(&ttl_delta, sizeof(ttl_delta), 1);
	}
}

void do_fork(bool initial) {
	pid = fork();
	if(pid == 0)
		setup_child();
	else if (pid > 0 && initial) 
		setup_parent();
	else {
		std::cerr << "Failed to fork Sandbox" << std::endl;
		exit(1);
	}
}

signed long Sandbox::run(const ByteArray &dna) {
	inqueue.send(&dna[0], dna.size(), 1);
	signed long ttl_delta = 0;
	std::size_t recvd = 0;
	unsigned int priority = 0;
	boost::system_time timeout = boost::get_system_time() + boost::seconds(SANDBOX_TIMEOUT);
	if(outqueue.timed_receive(&ttl_delta, sizeof(ttl_delta), &recvd, &priority, timeout)) {
		return ttl_delta;
	}
	else {
		// failed, kill and restart process
		kill(pid, SIGKILL);
		do_fork(false);
		throw timeout_error();
	}
}

