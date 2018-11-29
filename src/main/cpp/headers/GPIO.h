#pragma once

class GPIO {
	public:
		static bool get(const int &pin);
		static void set(const int &pin, const bool &value);

	private:
		static bool exported[27];
		static bool directions[27]; //false = input, true = output

		//Possible GPIO interactions https://www.kernel.org/doc/Documentation/gpio/sysfs.txt
		static void setexport(const int &pin, const bool &exp); //true = export, false = unexport
		static void setdirection(const int &pin, const char &option); //options: 'I', 'O', 'L', 'H' (in, out, low, high)
		static void setval(const int &pin, const bool &on); //true = high, false = low
		static int getval(const int &pin);
};