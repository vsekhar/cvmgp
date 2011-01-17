#ifndef __bytearray_hpp__
#define __bytearray_hpp__

#include <vector>

typedef unsigned char byte;
typedef std::vector<byte> ByteArray;

#if 0
struct ByteArray : public std::vector<byte> {
	typedef std::vector<byte> baseType;
	ByteArray() : std::vector<byte>() {}
	ByteArray(std::size_t s) : std::vector<byte>(s) {}
	ByteArray(byte*, std::size_t);
};
#endif

ByteArray make_ByteArray(byte*, std::size_t);
ByteArray random_ByteArray(std::size_t, std::size_t);

#endif

