#include <iostream>

#include <boost/random.hpp>
#include <boost/foreach.hpp>

#include "protein.hpp"
#include "vm.hpp"
#include "state.hpp"
#include "random.hpp"
#include "sandbox.hpp"
#include "exception.hpp"

int main() {

	const std::size_t protein_count = 1000000;
	Sandbox sandbox;	// create before creating Proteins
	Proteins soup(protein_count);
	for(unsigned int i = 0; i < protein_count; ++i)
		soup.push_back(Protein());
	
	// Generation loop
	unsigned long generations = 0;
	state_type state;
	while(1) {
		// Run loop
		for(int i = 0; i < 10; i++) {
			unsigned int rand_idx = random_uint(0, soup.size()-1);
			try {
				soup[rand_idx].ttl += sandbox.run(soup[rand_idx].dna);
			}
			catch(timeout_error &e) {
				// timeout penalty
				soup[rand_idx].ttl -= 1;
			}
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

