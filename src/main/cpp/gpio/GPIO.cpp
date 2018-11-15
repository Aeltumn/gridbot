#include <string>
#include <fstream> //File IO
#include <iostream>

#include "../headers/GPIO.h"

bool GPIO::exported[27];
bool GPIO::directions[27];

#if defined(__linux__) || defined(__CYGWIN__)
/* Public Methods */

//Read what a pin is currently set to, or read from an input pin.
bool GPIO::get(const int &pin) {
	if (pin < 0 || pin>26) throw "Pin must be between 0 and 26! (inclusive)";
	if (!GPIO::exported[pin]) GPIO::setexport(pin, true);
	if (GPIO::directions[pin]) GPIO::setdirection(pin, 'I');
	return GPIO::getval(pin);
}

//Set the value of an output pin, must be an output pin!
void GPIO::set(const int &pin, const bool &value) {
	if (pin < 0 || pin>26) throw "Pin must be between 0 and 26! (inclusive)";
	if (!GPIO::exported[pin]) GPIO::setexport(pin, true);
	if (!GPIO::directions[pin]) GPIO::setdirection(pin, 'O');
	GPIO::setval(pin, value);
	//if(!value) GPIO::setexport(pin, false); //If we set the output to off, also unexport.
}

/* Private Methods */

void GPIO::setexport(const int &pin, const bool &exp) {
	std::string s = exp ? "/sys/class/gpio/export" : "/sys/class/gpio/unexport";
	std::ofstream estream(s.c_str());
	estream << pin;
	estream.close();
	exported[pin] = exp;
}

void GPIO::setdirection(const int &pin, const char &option) {
	std::string s = "/sys/class/gpio/gpio" + pin;
	s.append("/direction");
	std::ofstream estream(s.c_str());
	estream << (option == 'I' ? "in" : option == 'O' ? "out" : option == 'H' ? "high" : "low");
	estream.close();
	directions[pin] = (option == 'I' ? false : true);
}

void GPIO::setval(const int &pin, const bool &on) {
	std::string s = "/sys/class/gpio/gpio" + pin;
	s.append("/value");
	std::ofstream estream(s.c_str());
	estream << on ? "1" : "0";
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
bool GPIO::get(const int &pin) { return false; }
void GPIO::set(const int &pin, const bool &value) {}
void GPIO::setexport(const int &pin, const bool &exp) {}
void GPIO::setdirection(const int &pin, const char &option) {}
void GPIO::setval(const int &pin, const bool &on) {}
int GPIO::getval(const int &pin) { return 0; }
#endif