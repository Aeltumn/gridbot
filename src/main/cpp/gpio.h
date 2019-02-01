#pragma once

class GPIO {
	private:
		//Possible GPIO interactions https://www.kernel.org/doc/Documentation/gpio/sysfs.txt
		static void setexport(const int &pin, const bool &exp); //true = export, false = unexport
		static void setdirection(const int &pin, const bool &out); //options: 'I', 'O' (in, out), O = true
		static void setval(const int &pin, const bool &on); //true = high, false = low
		static int getval(const int &pin);

	public:
		static bool get(const int &pin);
		static void set(const int &pin, const bool &value);
		static void initialise(const int &port1);
		static void initialise(const int &port1, const int &port2, const int &port3, const int &port4);
};