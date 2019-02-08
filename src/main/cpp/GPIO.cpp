#include "pch.h"

/*
	The GPIO works in a way where we need to first let it know which pins we wish
	to use and edit, we do this by exporting the pins. (we can unexport to let them go but exporting doesn't
	block other programs from also exporting so it doesn't matter)

	After exporting we can set the direction which is whether the pin should output a signal or wait for a signal,
	we can set direction to four values 'in', 'out', 'low' and 'high',
	low and high are basically the same as out, they function as out, but they setup the value as low or high,
	e.g. they auto-call set(pin, 1) for high and set(pin, 0) for low.
*/

void GPIO::initialise(const int &pin) {
	//Export pin
	std::ofstream estream("/sys/class/gpio/export");
	estream << pin << std::endl;
	estream.close();

	//Set direction to 'out'
	std::string s = std::string("/sys/class/gpio/gpio");
	s.append(std::to_string(pin));
	s.append("/direction");
	std::ofstream estream(s.c_str());
	estream << std::string("out") << std::endl;
	estream.close();
}
void GPIO::initialise(const int &port1, const int &port2, const int &port3, const int &port4) {
	initialise(port1); initialise(port2); initialise(port3); initialise(port4);
}

//Read what a pin is currently set to, or read from an input pin.
bool GPIO::get(const int &pin) {
	if (pin < 0 || pin>40) throw "Pin must be between 0 and 40! (exclusive)";
	std::string s = "/sys/class/gpio/gpio" + pin;
	s.append("/value");
	std::ifstream estream(s.c_str());
	std::string ret;
	estream >> ret;
	estream.close();
	return ret == "0" ? 0 : 1;
}

//Set the value of an output pin, must be an output pin!
void GPIO::set(const int &pin, const bool &value) {
	if (pin < 0 || pin>40) throw "Pin must be between 0 and 40! (exclusive)";
	std::string s = "/sys/class/gpio/gpio";
	s.append(std::to_string(pin));
	s.append("/value");
	std::ofstream estream(s.c_str());
	estream << (value ? "1" : "0") << std::endl;
	estream.close();
}