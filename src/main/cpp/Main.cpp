#include "pch.h"
#include "action/tictactoe.h"
#include <chrono>

int main() {
	//Setup thread pool
	/*
		Threads:
			- Processing Thread
				Take all data and determine exact movements to accomplish
				goals, i.e. take camera data and process it.
			- Action Thread
				Thread to determine next action in current game.
				Has purely general overview of current game being played.
			- Incoming Thread
				Process incoming camera data from socket connection.

			Support Threads:
			- GPIO Thread
				Constantly scans for queued movements and executes them in a fifo manner.
	
			In General:
				 Generally a cycle of commands should go as follows:
				 The incoming chat recieves a command, this command is either sent directly to the GPIO (if its a raw move command)
				 or it's seen as input and sent to the processing thread.
				 The processing thread parses incoming raw data, like moved piece 7 from A1 to G8 or
				 camera action in xyz something.
				 The processing thread stores this data into the general game view which is managed by the action thread.
				 The action thread looks at the game view and constantly comes up with possible strategies but thinks
				 of reactions in particular to recent changes.
				 The action thread has a queue ready of the moves it sees as best at this time.
				 
				 Whenever the Incoming Thread gets notified it may take a turn it instructs the GPIO thread to
				 take the next move from the queue and execute that. There should be a between thread bridge
				 for this that changes gameplan A1->G8 to cm.
	
				Bottom-left corner: (0,0)
	*/

	try {
		std::thread incoming(Logger::setup);
		while (!Logger::isConnected()) {} //Block until logger has connected
		Logger::info("Starting up Gridbot v1.0");// #@BUILD_NUMBER@");
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

		using namespace std::literals::chrono_literals;
		while (true) {
			//Just keep spamming 'em
			Logger::ping();
			std::this_thread::sleep_for(90s);
		}
		//action.join(); //We need to join a thread when the main thread has nothing else to do.
	} catch (const std::exception& e) {
		Logger::info(e.what());
		return 0;
	}
} 