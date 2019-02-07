#pragma once

//Possible GPIO interactions https://www.kernel.org/doc/Documentation/gpio/sysfs.txt

class GPIO {
	public:
		static bool get(const int &pin);
		static void set(const int &pin, const bool &value);
		static void initialise(const int &port1);
		static void initialise(const int &port1, const int &port2, const int &port3, const int &port4);
};