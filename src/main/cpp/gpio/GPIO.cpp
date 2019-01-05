#include "../pch.h"
#include <fstream> //File IO

#if defined(__linux__)
/* Public Methods */

void GPIO::initialise(const int &port1, const int &port2, const int &port3, const int &port4) {
	setexport(port1, true);
	setdirection(port1, true);

	setexport(port2, true);
	setdirection(port2, true);

	setexport(port3, true);
	setdirection(port3, true);

	setexport(port4, true);
	setdirection(port4, true);
}

//Read what a pin is currently set to, or read from an input pin.
bool GPIO::get(const int &pin) {
	if (pin < 0 || pin>40) throw "Pin must be between 0 and 26! (inclusive)";
	return GPIO::getval(pin);
}

//Set the value of an output pin, must be an output pin!
void GPIO::set(const int &pin, const bool &value) {
	if (pin < 0 || pin>40) throw "Pin must be between 0 and 26! (inclusive)";
	char buf[256];
	buf[0] = 0;
	strcat(buf, "[GPIO] Setting ");
	strcat(buf, std::to_string(pin).c_str());
	strcat(buf, " to ");
	strcat(buf, std::to_string(value).c_str());
	strcat(buf, ".");
	Logger::info(buf);
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
	//May we never forgot the original line of code blow
	//which caused 5 hours of debugging, originally, this stood below:
	//  std::string s = "/sys/class/gpio/gpio" + pin;
	//Thanks to this great language that bugged out and never added the pin.

	std::string s = "/sys/class/gpio/gpio";
	s.append(std::to_string(pin));
	s.append("/direction");
	std::ofstream estream(s.c_str());
	estream << std::string(out ? "out" : "in") << std::endl;
	estream.close();
	//directions[pin] = out;
}

void GPIO::setval(const int &pin, const bool &on) {
	std::string s = "/sys/class/gpio/gpio";
	s.append(std::to_string(pin));
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