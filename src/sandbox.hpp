#ifndef __sandbox_hpp_
#define __sandbox_hpp_

#include <sys/types.h>

#include <boost/interprocess/ipc/message_queue.hpp>

#include "sandbox_fwd.hpp"
#include "protein.hpp"

#define SANDBOX_TIMEOUT (10)

enum msgType {DONE, REQ_PROTEIN};

struct Message {
	msgType type;
	byte dna[PROTEIN_MAX_LENGTH];
	std::size_t dna_size;
};

struct Sandbox {
	Sandbox();
	~Sandbox();
	signed long run(const ByteArray&);
private:
	void run_child();
	void do_fork();
	pid_t pid;
	::boost::interprocess::message_queue inqueue;
	::boost::interprocess::message_queue outqueue;
};

#endif

