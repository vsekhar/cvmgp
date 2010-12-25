#ifndef __random_hpp__
#define __random_hpp__

#include <boost/random/mersenne_twister.hpp>

extern boost::mt19937 generator;

unsigned int random_uint(unsigned int, unsigned int);
signed int random_int(signed int, signed int);

#endif

