#ifndef __sandbox_hpp_
#define __sandbox_hpp_

#include <sys/types.h>

#include <boost/interprocess/ipc/message_queue.hpp>

#include "bytearray.hpp"

#define SANDBOX_TIMEOUT (10)

struct Sandbox {
	Sandbox();
	~Sandbox();
	signed long run(const ByteArray&);
private:
	void setup_parent();
	void setup_child();
	void do_fork();
	pid_t pid;
	::boost::interprocess::message_queue inqueue;
	::boost::interprocess::message_queue outqueue;
};

#endif

