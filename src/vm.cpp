#include <boost/thread/thread.hpp>

#include <sys/types.h>

#include "vm.hpp"
#include "exception.hpp"

/* Goals
	Starting list:
	Runs without throwing exception during time limit (1)
	Runs without throwing exception and terminates in time limit(5)
	
	Possible future ones:
	Runs, reads and writes test input value (10)
	Runs, reads and writes dna of another org (15)
	Runs, reads and writes (copies) its own dna (25)
	// some more
	Runs, replaces another org's dna with its own (100)
*/

struct State {
	State() : sandbox(0), actionflag(0) {}
	Sandbox* sandbox;
	unsigned int actionflag;
};

void vm_run_dna (const ByteArray &dna, State &state) {
	// massive switch statement, etc.
	ByteArray::const_iterator ip = dna.begin();
	while(ip != dna.end()) {
		switch(*(ip++)) {
			case 0: break;
			case 1: // do something
					break;
			// etc.
			default: throw opcode_error();
		}
	}
}

signed long vm_tester(const ByteArray &dna, Sandbox* sandbox) {
	State state;
	state.sandbox = sandbox;
	try {
		vm_run_dna(dna, state);
	}
	catch(opcode_error &e) {}
	// test based on output of state and determine ttl delta
	return 0;
}

