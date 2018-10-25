#include "GPIO.cpp"

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
				Process incoming commands and camera data from socket connections.
	*/

	//bool va = GPIO::get(5);
	//GPIO::set(26, true);
}