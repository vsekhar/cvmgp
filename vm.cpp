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

void vm_run_dna (const ByteArray &dna, state_type &state) {
	// massive switch statement, etc.
	ByteArray::const_iterator ip = dna.begin();
	while(ip != dna.end()) {
		switch(*(ip++)) {
			case 0: break;
			case 1: // do something
					break;
			// etc.
			default: throw badopcode_error();
		}
	}
}

signed long vm_tester(const ByteArray &dna, const state_type &state) {
	// do some testing, return a ttl delta
	return 0;
}

void vm_thread (const ByteArray &dna, state_type &state) {
	// Handles exceptions coming out of the switch statement
	try vm_run_dna(dna, state);
	catch (badopcode_error &e) {}
	
	
	
}

signed long vm_run(const ByteArray &dna, state_type &state) {
	signed long ttl_delta = 0;
	pid_t child_id = vfork();
	if(child_id) {	// parent
		// monitor child and terminate if it takes too long
		// sleep (n seconds)
		// 
	}
	else {			// child
		vm_thread(dna,state);
		exit(0);
		
	}
	
	// run the program
	// update state
	// test for goals passed or failed
	// ttl_delta = sum(goal_rewards) - sum(goal_penalties)
	return 0; //TTL delta
}

