#include <ctime>

#include <boost/random/uniform_int.hpp>
#include <boost/random/variate_generator.hpp>

#include "random.hpp"

unsigned int random_uint(unsigned int min, unsigned int max) {
	boost::uniform_int<> dist(min, max);
    boost::variate_generator<boost::mt19937&, boost::uniform_int<> > die(generator, dist);
    return die();
}

ByteArray random_string(std::size_t min, std::size_t max) {
	std::size_t length = random_uint(min, max);
	ByteArray ret(length);
	for(std::size_t i = 0; i < length; i++)
		ret.push_back(random_uint(0, (1<<8)-1));

	return ret;
}

boost::mt19937 generator(std::time(0));

