#include "bytearray.hpp"

ByteArray::ByteArray(byte* src, std::size_t size) {
	baseType::reserve(size);
	std::copy(src, src + size, std::back_inserter(*this));
}

