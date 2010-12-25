#include <boost/random/uniform_int.hpp>
#include <boost/random/variate_generator.hpp>

#include "random.hpp"

unsigned int random_uint(unsigned int min, unsigned int max) {
	boost::uniform_int<> dist(min, max);
    boost::variate_generator<boost::mt19937&, boost::uniform_int<> > die(generator, dist);
    return die();
}
