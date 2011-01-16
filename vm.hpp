#ifndef __vm_hpp__
#define __vm_hpp__

#include "bytearray.hpp"
#include "state.hpp"

signed long vm_run(const ByteArray &, state_type &);

#endif

