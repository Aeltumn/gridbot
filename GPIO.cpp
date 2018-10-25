#include <string>
#include <fstream> //File IO
#include <iostream>

#include "GPIO.h"

/* Public Methods */

//Read what a pin is currently set to, or read from an input pin.
bool GPIO::get(int pin) {
	if (pin < 0 || pin>26) throw "Pin must be between 0 and 26! (inclusive)";
	if (!GPIO::inst.exported[pin]) GPIO::inst.export(pin, true);
	if (GPIO::inst.directions[pin]) GPIO::inst.direction(pin, 'I');
	return GPIO::inst.getval(pin);
}

//Set the value of an output pin, must be an output pin!
void GPIO::set(int pin, bool value) {
	if (pin < 0 || pin>26) throw "Pin must be between 0 and 26! (inclusive)";
	if (!GPIO::inst.exported[pin]) GPIO::inst.export(pin, true);
	if (!GPIO::inst.directions[pin]) GPIO::inst.direction(pin, 'O');
	GPIO::inst.setval(pin, value);
	//if(!value) GPIO::inst.export(pin, false); //If we set the output to off, also unexport.
}

/* Private Methods */

void GPIO::export(int pin, bool export) {
	std::string s = export ? "/sys/class/gpio/export" : "/sys/class/gpio/unexport";
	std::ofstream estream(s.c_str());
	estream << pin;
	estream.close();
	exported[pin] = export;
}

void GPIO::direction(int pin, char option) {
	std::string s = "/sys/class/gpio/gpio" + pin;
	s.append("/direction");
	std::ofstream estream(s.c_str());
	estream << (option == 'I' ? "in" : option == 'O' ? "out" : option == 'H' ? "high" : "low");
	estream.close();
	directions[pin] = (option == 'I' ? false : true);
}

void GPIO::setval(int pin, bool on) {
	std::string s = "/sys/class/gpio/gpio" + pin;
	s.append("/value");
	std::ofstream estream(s.c_str());
	estream << on ? "1" : "0";
	estream.close();
}

int GPIO::getval(int pin) {
	std::string s = "/sys/class/gpio/gpio" + pin;
	s.append("/value");
	std::ifstream estream(s.c_str());
	std::string ret;
	estream >> ret;
	estream.close();
	return ret == "0" ? 0 : 1;
}