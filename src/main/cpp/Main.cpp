#include "headers/GPIO.h"
#include "headers/Logger.h"
#include <thread>

int main() {
	//Setup thread pool
	/*
		Threads:
			- GPIO Thread
				Handles outputs to GPIO based on current state goal.
				Also takes the raw movement (move A1 to G2) to fine
				movement. (5 cm left, 3 cm up)
			- Processing Thread
				Take all data and determine exact movements to accomplish
				goals, i.e. take camera data and game plan to queue up
				raw movement.
			- Action Thread
				Thread to determine next action in current game.
				Has purely general overview of current game being played.
			- Incoming Thread
				Process incoming camera data from socket connection.
	*/

	std::thread incoming(Logger::setup);
	Logger::info("Starting up Gridbot v1.0 #${BUILD_NUMBER}");
	return 0;
}