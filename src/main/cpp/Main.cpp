#include "headers/GPIO.h"
#include "headers/Logger.h"
#include "headers/Motor.h"
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
	
			GENERAL:
				Generally a cycle of commands should go as follows:
				 The Incoming chat recieves a command, this command is either sent directly to the GPIO (if its a raw move command)
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
	*/

	std::thread incoming(Logger::setup);
	Logger::info("Starting up Gridbot v1.0 #[BUILD_NUMBER]");

	using namespace distanceunits;
	Motor(29, 31, 33, 35).move(1.0cm);
	return 0;
}