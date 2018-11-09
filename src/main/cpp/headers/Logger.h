#ifndef LOGGER_H_
#define LOGGER_H_
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

class Logger {
	public:
		static void setup();
		static void info(const char* txt);
};
#endif