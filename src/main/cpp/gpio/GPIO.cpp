#include "../pch.h"
#include <fstream> //File IO

#if defined(__linux__)
/* Public Methods */

void GPIO::initialise() {
	for (int i = 0; i <= 26; i++) {
		setexport(i, true);
		setdirection(i, true);
	}
}

//Read what a pin is currently set to, or read from an input pin.
bool GPIO::get(const int &pin) {
	if (pin < 0 || pin>26) throw "Pin must be between 0 and 26! (inclusive)";
	return GPIO::getval(pin);
}

//Set the value of an output pin, must be an output pin!
void GPIO::set(const int &pin, const bool &value) {
	if (pin < 0 || pin>26) throw "Pin must be between 0 and 26! (inclusive)";
	GPIO::setval(pin, value);
	//if(!value) GPIO::setexport(pin, false); //If we set the output to off, also unexport.
}

/* Private Methods */

void GPIO::setexport(const int &pin, const bool &exp) {
	std::string s = exp ? "/sys/class/gpio/export" : "/sys/class/gpio/unexport";
	std::ofstream estream(s.c_str());
	estream << pin << std::endl;
	estream.close();
	//exported[pin] = exp;
}

void GPIO::setdirection(const int &pin, const bool &out) {
	std::string s = "/sys/class/gpio/gpio" + pin;
	s.append("/direction");
	std::ofstream estream(s.c_str());
	Logger::info(s.c_str());
	estream << std::string("out") << std::endl;//out ? "out" : "in";
	estream.close();

	std::ifstream e2stream(s.c_str());
	std::string ret;
	e2stream >> ret;
	e2stream.close();
	Logger::info(ret.c_str());
	//directions[pin] = out;
}

void GPIO::setval(const int &pin, const bool &on) {
	std::string s = "/sys/class/gpio/gpio" + pin;
	s.append("/value");
	std::ofstream estream(s.c_str());
	estream << (on ? "1" : "0") << std::endl;
	estream.close();
}

int GPIO::getval(const int &pin) {
	std::string s = "/sys/class/gpio/gpio" + pin;
	s.append("/value");
	std::ifstream estream(s.c_str());
	std::string ret;
	estream >> ret;
	estream.close();
	return ret == "0" ? 0 : 1;
}
#else
void GPIO::initialise() {}
bool GPIO::get(const int &pin) { return false; }
void GPIO::set(const int &pin, const bool &value) {}
void GPIO::setexport(const int &pin, const bool &exp) {}
void GPIO::setdirection(const int &pin, const bool &out) {}
void GPIO::setval(const int &pin, const bool &on) {}
int GPIO::getval(const int &pin) { return 0; }
#endif