#include "pch.h"
#include "tictactoe.h"

int main() {
	/*
		Threads:
			- incoming - Logger -> Constantly waiting for new input from grinterface.dgoossens.nl.
			- action - Beta -> The thread doing calculations on which moves to do next.
			- gpio - Biker -> The thread which executes motor movement instructions,
				these instructions can be queued at any time and are ran sperately by the gpio thread.
	*/

	try {
		std::thread incoming(Logger::setup);
		while (!Logger::isConnected()) {} //Block until logger has connected
		Logger::info("Starting up Gridbot v1.0 #45");
		std::thread action(Beta::startup);
		std::thread gpio(Biker::setup);

		//Clear GPIO
		GPIO::initialise(4, 17, 27, 22); //7, 11, 13, 15
		GPIO::initialise(18, 23, 24, 25); //12, 16, 18, 22
		GPIO::initialise(6, 13, 19, 26); //31, 33, 35, 37
		GPIO::initialise(12, 16, 20, 21); //32, 36, 38, 40
		GPIO::initialise(10); //19

		using namespace distanceunits;
		Motor x = Motor(4, 17, 27, 22);
		Motor xmirror = Motor(6, 13, 19, 26);
		Motor y = Motor(18, 23, 24, 25);
		Motor z = Motor(12, 16, 20, 21);

		x.setmimic(&xmirror);
		Beta::setmotors(&x, &y, &z);
		Beta::runGame(new TicTacToe(true, EASY));

		action.join(); //We need to join a thread when the main thread has nothing else to do.
	} catch (const std::exception& e) {
		Logger::info(e.what());
		return 0;
	}
} 