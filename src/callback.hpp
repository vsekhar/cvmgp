#ifndef __callback_hpp__
#define __callback_hpp__

#include <boost/python/call.hpp>

template <typename R, typename A1>
struct CallBack {
	CallBack(PyObject *c) :
		_callable(::boost::python::incref(c))
	{};
	~CallBack() {
		::boost::python::decref(c);
	}
	R operator()(A1) {
		namespace bp = ::boost::python;
		return bp::call<R>(_callable);
	}

private:
	PyObject* _callable;

};

#endif

