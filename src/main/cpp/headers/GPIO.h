#ifndef GPIO_H_
#define GPIO_H_
#include <string>

class GPIO {
	public:
		static bool get(int pin);
		static void set(int pin, bool value);

	private:
		static bool exported[27];
		static bool directions[27]; //false = input, true = output

		//Possible GPIO interactions https://www.kernel.org/doc/Documentation/gpio/sysfs.txt
		static void setexport(int pin, bool exp); //true = export, false = unexport
		static void setdirection(int pin, char option); //options: 'I', 'O', 'L', 'H' (in, out, low, high)
		static void setval(int pin, bool on); //true = high, false = low
		static int getval(int pin);
};
#endif