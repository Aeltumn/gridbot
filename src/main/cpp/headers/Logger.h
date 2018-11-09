#ifndef LOGGER_H_
#define LOGGER_H_
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <string.h>

class Logger {
	public:
		static void setup();
		static void info(const char* txt);
		static void error(const char* txt);
};
#endif