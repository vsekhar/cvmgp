#include <sstream>

#include <boost/foreach.hpp>
#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>

#include <boost/python/call.hpp>
#include <boost/python/object/pickle_support.hpp>

#include "bytearray.hpp"
#include "callback.hpp"

namespace bp = ::boost::python;

void caller(PyObject* func, unsigned int i) {
	using namespace ::boost::python;
	for(unsigned int j=0; j<i; j++)
		call<void>(func, i);
}

struct ByteArray_pickle_suite : boost::python::pickle_suite {
	static
	boost::python::tuple
	getinitargs(const ByteArray&) {return boost::python::make_tuple();}
	
	static
	boost::python::tuple
	getstate(const ByteArray& b) {
		std::stringstream ss;
		ss << b;
		return boost::python::make_tuple(ss.str());
	}
	static
	void
	setstate(ByteArray& b, boost::python::tuple state) {
		using namespace boost::python;
		if (len(state) != 1) {
			PyErr_SetObject(PyExc_ValueError,
				("expected 1-item tuple in call to __setstate__; got %s" % state).ptr());
			throw_error_already_set();
		}
		std::string s = extract<std::string>(state[0]);
		b.reserve(s.size());
		std::copy(s.begin(), s.end(), std::back_inserter(b));
	}
};

boost::python::dict make_population(int n, int min, int max) {
	boost::python::list l;
	for(int i = 0; i < n; i++)
		l.append(random_ByteArray(min, max));
	boost::python::dict d;
	d[""] = l;
	return d;
}

BOOST_PYTHON_MODULE(_vmgp) {
	using namespace ::boost::python;
	class_<ByteArray>("ByteArray", init<>())
		.def(vector_indexing_suite<ByteArray>())
		.def(self_ns::str(self))
		.def_pickle(ByteArray_pickle_suite());
	def("make_ByteArray", make_ByteArray);
	def("random_ByteArray", random_ByteArray);
	def("make_population", make_population);

	typedef CallBack<int, std::string> lenner;

	// tests
	def("caller", caller);
	class_<lenner>("lenner", init<PyObject*>())
		.def("__call__", &lenner::operator());
}

