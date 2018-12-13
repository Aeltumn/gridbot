#include "../pch.h"
#include <chrono>

/* Public Methods */
Motor::Motor(const int &port1, const int &port2, const int &port3, const int &port4) { p1 = port1; p2 = port2; p3 = port3; p4 = port4; }

void Motor::setmimic(Motor *mimi) { mimic = mimi; }
void Motor::queue(const long double &centimeters) { Biker::push(QueuedAction(centimeters, this)); }
void Motor::moveint(const long double &centimeters) {
	if(mimic) mimic->moveint(centimeters); //null pointers become FALSE automatically
	for (long long ind = (long long) std::round(centimeters); ind > 0; --ind) {
		using namespace std::literals::chrono_literals;
		///Steps 1 and 3 are the same for (counter)clockwise.
		///Steps 2 and 4 are reversed, so step 2 for clockwise is step 4 for counterclockwise and visa versa.
		//Step 1
		GPIO::set(p1, true); GPIO::set(p2, false); GPIO::set(p3, false); GPIO::set(p4, true);
		std::this_thread::sleep_for(200ms);
		
		//IOOI
		//IIOO
		//OIIO
		//OOII

		//Step 2
		if (centimeters > 0) {
			//Positive = Clockwise
			GPIO::set(p1, true); GPIO::set(p2, true); GPIO::set(p3, false); GPIO::set(p4, false);
			std::this_thread::sleep_for(200ms);
		} else {
			//Negative = Counter-Clockwise
			GPIO::set(p1, false); GPIO::set(p2, false); GPIO::set(p3, true); GPIO::set(p4, true);
			std::this_thread::sleep_for(200ms);
		}

		//Step 3
		GPIO::set(p1, false); GPIO::set(p2, true); GPIO::set(p3, true); GPIO::set(p4, false);
		std::this_thread::sleep_for(200ms);

		//Step 4
		if (centimeters <= 0) {
			//Negative = Counter-Clockwise
			GPIO::set(p1, true); GPIO::set(p2, true); GPIO::set(p3, false); GPIO::set(p4, false);
			std::this_thread::sleep_for(200ms);
		} else {
			//Positive = Clockwise
			GPIO::set(p1, false); GPIO::set(p2, false); GPIO::set(p3, true); GPIO::set(p4, true);
			std::this_thread::sleep_for(200ms);
		}
	}

	//Cleaup after ourselves
	GPIO::set(p1, false); GPIO::set(p2, false); GPIO::set(p3, false); GPIO::set(p4, false);
}