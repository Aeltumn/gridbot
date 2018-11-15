#ifndef LOGGER_H_
#define LOGGER_H_
#include <sys/types.h>

class Logger {
	public:
		static void setup();
		static void info(const char* txt);
		static void error(const char* txt);
};
#endif