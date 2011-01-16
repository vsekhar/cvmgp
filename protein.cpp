#include "protein.hpp"
#include "random.hpp"

Protein::Protein() {
	ttl = PROTEIN_INITIAL_TTL;
	dna = random_string(PROTEIN_INITIAL_LENGTH_MIN, PROTEIN_INITIAL_LENGTH_MAX);
}

