#ifndef __random_hpp__
#define __random_hpp__

#include <boost/random/mersenne_twister.hpp>

#include "bytearray.hpp"

extern boost::mt19937 generator;

unsigned int random_uint(unsigned int, unsigned int);
signed int random_int(signed int, signed int);

ByteArray random_string(std::size_t, std::size_t);

#endif

