#pragma once
#include <string>

class GPIO {
	public:
		static bool get(int pin);
		static void set(int pin, bool value);

	private:
		static GPIO inst;
		bool exported[27];
		bool directions[27]; //false = input, true = output

		//Possible GPIO interactions https://www.kernel.org/doc/Documentation/gpio/sysfs.txt
		void export(int pin, bool export); //true = export, false = unexport
		void direction(int pin, char option); //options: 'I', 'O', 'L', 'H' (in, out, low, high)
		void setval(int pin, bool on); //true = high, false = low
		int getval(int pin);
};