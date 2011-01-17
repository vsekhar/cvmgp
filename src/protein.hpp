#ifndef __protein_hpp__
#define __protein_hpp__

#include <vector>

#include "bytearray.hpp"

#define PROTEIN_INITIAL_TTL (10)
#define PROTEIN_INITIAL_LENGTH_MIN (5)
#define PROTEIN_INITIAL_LENGTH_MAX (100)
#define PROTEIN_MAX_LENGTH (1024)

struct Protein {
	Protein();
	Protein(const ByteArray& b, unsigned long i) : dna(b), ttl(i) {}
	ByteArray dna;
	unsigned long ttl;
};

typedef std::vector<Protein> Proteins;

#endif

