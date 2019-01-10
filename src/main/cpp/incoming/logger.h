#pragma once

class Logger {
	public:
		static void setup();
		static void info(const char* txt);
		static void error(const char* txt);
		static bool isConnected();
		static void ping();
};