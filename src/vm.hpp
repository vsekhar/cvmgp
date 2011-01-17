#include <string>
#include <boost/python.hpp>

#include "bytearray.hpp"

struct VMMessage {
	std::string type;
	std::string payload;
}

class VM {
	VM();

	std::size_t _ip;
	ByteArray _dna;
	std::string _request;

public:
	void reset();
	void set_dna(ByteArray);
	bool done();
	void run();
	std::string get_request();
	void put_response(std::string);
};

