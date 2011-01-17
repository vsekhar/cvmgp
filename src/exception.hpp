#ifndef __exceptions_hpp__
#define __exceptions_hpp__

#include <stdexcept>

struct exec_error : std::runtime_error {
	exec_error() : std::runtime_error("") {}
};
struct opcode_error : exec_error {};
struct timeout_error : exec_error {};

#endif

