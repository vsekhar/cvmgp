#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

#include <boost/python/call.hpp>

#include "bytearray.hpp"
#include "callback.hpp"

namespace bp = ::boost::python;

void caller(PyObject* func, unsigned int i) {
	using namespace ::boost::python;
	for(unsigned int j=0; j<i; j++)
		call<void>(func, i);
}


BOOST_PYTHON_MODULE(_vmgp) {
	using namespace ::boost::python;
	class_<ByteArray>("ByteArray", init<>())
		.def(vector_indexing_suite<ByteArray>());
	def("random_ByteArray", random_ByteArray);
	
	typedef CallBack<int, std::string> lenner;

	// tests
	def("caller", caller);
	class_<lenner>("lenner", init<PyObject*>())
		.def("__call__", &lenner::operator());
}

