#include "pch.h"

int main() {
	/*
		Threads:
			- incoming - Logger -> Constantly waiting for new input from grinterface.dgoossens.nl.
			- action - Beta -> The thread doing calculations on which moves to do next.
			- gpio - Biker -> The thread which executes motor movement instructions,
				these instructions can be queued at any time and are ran sperately by the gpio thread.
	*/

	try {
		// We start by starting the incoming or Logger thread, this will establish a connection grinterface.dgoossens.nl
		std::thread incoming(Logger::setup);
		while (!Logger::isConnected()) {} //Block until logger has connected, only after the logger is connected can we read the Logger::info outputs so it's important to get this connected asap

		// From here on we can use the logger.
		Logger::info("Starting up Gridbot v1.0 #45");

		// We start the action and gpio threads next
		std::thread action(Beta::startup);
		std::thread gpio(Biker::setup);

		// We initialise all used GPIO ports, here we claim and initialise them all
		GPIO::initialise(4, 17, 27, 22); //7, 11, 13, 15
		GPIO::initialise(18, 23, 24, 25); //12, 16, 18, 22
		GPIO::initialise(6, 13, 19, 26); //31, 33, 35, 37
		GPIO::initialise(12, 16, 20, 21); //32, 36, 38, 40
		GPIO::initialise(10); //19

		// Now we initialise the various motors and set them so they can be used.
		using namespace distanceunits;
		Motor x = Motor(4, 17, 27, 22);
		Motor xmirror = Motor(6, 13, 19, 26);
		Motor y = Motor(18, 23, 24, 25);
		Motor z = Motor(12, 16, 20, 21);

		x.setmimic(&xmirror); // We have two x motors where they mimic one another so they both drive fowards.
		Beta::setmotors(&x, &y, &z);
		action.join(); //We need to join a thread when the main thread has nothing else to do.
	} catch (const std::exception& e) {
		Logger::info(e.what());
		return 0;
	}
} 