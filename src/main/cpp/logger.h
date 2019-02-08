#pragma once
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

class Logger {
	private:
		static void log(bool time_, const char* prefix, const char* str);

	public:
		static void setup();
		static void info(const char* txt);
		static void amend(const char* txt);
		static void error(const char* txt);
		static void warning(const char* txt);
		static void newline();
		static bool isConnected();
		static bool handleCommand(const char* txt);
};