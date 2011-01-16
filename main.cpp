#include <iostream>

#include <boost/random.hpp>
#include <boost/foreach.hpp>

#include "protein.hpp"
#include "vm.hpp"
#include "state.hpp"
#include "random.hpp"

int main() {

	// Create a bucket of strings with TTLs
	Proteins soup;
	for(unsigned int i = 0; i < 1000; ++i)
		soup.push_back(Protein());
	
	// Generation loop
	unsigned long generations = 0;
	state_type state;
	while(1) {
		// Run loop
		for(int i = 0; i < 10; i++) {
			unsigned int rand_idx = random_uint(0, soup.size()-1);
			soup[rand_idx].ttl += vm_run(soup[rand_idx].dna, state);
		}

		// Decay/stats loop
		double fitness_sum = 0;
		BOOST_FOREACH(Protein& o, soup) {
			--o.ttl;
			
			// replace dead org with new org
			if (o.ttl == 0)
				o = Protein();

			fitness_sum += o.ttl;
		}
		std::cout << "Gen " << generations << " fitness average: "
			<< (fitness_sum / soup.size()) << std::endl;

		generations++;
	}
}

