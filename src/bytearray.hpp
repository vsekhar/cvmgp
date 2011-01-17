#ifndef __bytearray_hpp__
#define __bytearray_hpp__

#include <vector>
#include <string>
#include <ostream>

typedef unsigned char byte;
typedef std::vector<byte> ByteArray;

namespace std {
std::ostream& operator<<(std::ostream&, const ByteArray&);
}

ByteArray make_ByteArray(byte*, std::size_t);
ByteArray random_ByteArray(std::size_t, std::size_t);

#endif

