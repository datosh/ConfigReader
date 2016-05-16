#include "ConfigReader.h"

#include <cassert>
#include <iostream>
#include <string>

ConfigReader* ConfigReader::s_instance;

class IPClass
{
public:
	IPClass(uint8_t a, uint8_t b, uint8_t c, uint8_t d) : a(a), b(b), c(c), d(d) {};

	IPClass(std::string ip)
	{
		size_t idx = ip.find('.');
		a = std::stoi(ip.substr(0, idx));
		
		size_t last_idx = idx;
		idx = ip.find('.', idx + 1);
		b = std::stoi(ip.substr(last_idx + 1, idx));

		last_idx = idx;
		idx = ip.find('.', idx + 1);
		c = std::stoi(ip.substr(last_idx + 1, idx));

		last_idx = idx;
		idx = ip.find('.', idx + 1);
		d = std::stoi(ip.substr(last_idx + 1, idx));
	}

	inline bool operator==(const IPClass& ipc)
	{
		return this->a == ipc.a && this->b == ipc.b && this->c == ipc.c && this->d == ipc.d;
	}

private:
	uint8_t a, b, c, d;
};

int main()
{
	ConfigReader* cr = ConfigReader::instance();

	assert(cr->get_as<int>("intvalue") == 5);
	assert(cr->get_as<double>("floatvalue") == 5.0f);
	assert(cr->get_as<bool>("boolvalue") == true);
	assert(cr->get_as<bool>("falsevalue") == false);
	assert(cr->get_as<IPClass>("ipvalue") == IPClass(11, 22, 33, 44));
	assert(cr->get_as<std::string>("stringvalue") == "test config file");

	try {
		std::cout << std::boolalpha << cr->get_as<bool>("errorbool") << " should be: error! PROBLEM!" << std::endl;
		return -1;
	}
	catch (std::invalid_argument& ia) 
	{
		std::cout << "errorbool is not a valid bool argument" << std::endl;
	}

	std::cout << "All tests passed!" << std::endl;

	return 0;
}