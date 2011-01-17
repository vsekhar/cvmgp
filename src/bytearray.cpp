#include <boost/python.hpp>

#include "bytearray.hpp"
#include "random.hpp"

ByteArray make_ByteArray(byte* src, std::size_t size) {
	ByteArray ret;
	ret.reserve(size);
	std::copy(src, src + size, std::back_inserter(ret));
	return ret;
}

ByteArray random_ByteArray(std::size_t min, std::size_t max) {
	std::size_t length = random_uint(min, max);
	ByteArray ret(length);
	for(std::size_t i = 0; i < length; i++)
		ret.push_back(random_uint(0, (1<<8)-1));
	return ret;
}

