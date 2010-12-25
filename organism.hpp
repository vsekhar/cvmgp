#ifndef __organism_hpp__
#define __organism_hpp__

#include <vector>

typedef unsigned char byte;
typedef std::vector<byte> ByteArray;

struct Organism {
	Organism() : dna(), ttl(0) {}
	Organism(unsigned long i) : dna(), ttl(i) {}
	Organism(const ByteArray& b, unsigned long i) : dna(b), ttl(i) {}
	ByteArray dna;
	unsigned long ttl;
};

typedef std::vector<Organism> Population;

#endif

