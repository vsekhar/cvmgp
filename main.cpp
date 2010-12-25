#include <iostream>

#include <boost/random.hpp>
#include <boost/foreach.hpp>

#include "organism.hpp"
#include "vm.hpp"
#include "state.hpp"

#define INITIAL_TTL (10)
#define INITIAL_LENGTH_MIN (5)
#define INITIAL_LENGTH_MAX (100)

int main() {

	// Create a bucket of strings with TTLs
	Population pop;
	for(unsigned int i = 0; i < 1000; ++i)
		pop.push_back(Organism());
	
	// Generation loop
	unsigned long generations = 0;
	state_type state;
	while(1) {
		// Run loop
		while (1) {
			unsigned int rand_idx = random_uint(0, pop.size()-1);
			pop[rand_idx].ttl += VirtualMachine(pop[rand_idx].dna, state);
		}

		// Decay loop
		while(1) {
			BOOST_FOREACH(Organism& o, pop) {
				--o.ttl;
				
				// replace dead org with new org
				if (o.ttl == 0) {
					o.ttl = INITIAL_TTL;
					o.dna = random_string(INITIAL_LENGTH_MIN, INITIAL_LENGTH_MAX);
				}
			}
		}
		
		generations++;
	}
}

