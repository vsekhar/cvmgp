#include <boost/thread/thread.hpp>

#include "vm.hpp"

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

void vm_runner (const ByteArray &dna, state_type &state) {
	// massive switch statement, etc.
}

signed long VirtualMachine(const ByteArray &dna, state_type &state) {
	signed long ttl_delta = 0;
	boost::thread runner(vm_runner, boost::cref(dna), boost::ref(state));
	
	// run the program
	// update state
	// test for goals passed or failed
	// ttl_delta = sum(goal_rewards) - sum(goal_penalties)
	return 0; //TTL delta
}

