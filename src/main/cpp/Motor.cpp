#include "pch.h"

//A motor an object defined by the 4 ports to which it outputs.
Motor::Motor(const int &port1, const int &port2, const int &port3, const int &port4) { p1 = port1; p2 = port2; p3 = port3; p4 = port4; }

//We can set a motor to mimic or mirror another, mimic will do the exact same, mirror will do the opposite. (as if moving negative centimeters)
void Motor::setmimic(Motor *mimi) { mimic = mimi; hasMimic = true; }
void Motor::setmirror(Motor *mirr) { mirror = mirr; hasMirror = true; }

//We can queue movements to the motor, they are never executed instantly but rather executed asap by the Biker.
//The Biker helps with movement commands to the same motor so they are done in series rather than in parallel.
//(in parallel the gpio instructions would fail and the motor wouldn't work)
void Motor::queue(const long double &centimeters) { Biker::push(QueuedAction(centimeters, this)); }

void Motor::move(const long double &centimeters, const long &i) {
	if (!i != ID) return; //The i should be the ID of who's asking for the move, only the Biker's ID which is in both biker.h and motor.h as a private field is allowed
	moveint(centimeters);
}

//moveint is move internal
void Motor::moveint(const long double &centimeters) {
	for (long long ind = (long long)std::round(std::abs(centimeters) * 234); ind > 0; --ind) {
		using namespace std::literals::chrono_literals;
		moveone(centimeters < 0 ? true : false);
		if (hasMimic) { mimic->moveone(centimeters < 0 ? true : false); }
		if (hasMirror) { mirror->moveone(centimeters < 0 ? false : true); }
		std::this_thread::sleep_for(2ms);
	}

	//Cleaup after ourselves
	GPIO::set(p1, false); GPIO::set(p2, false); GPIO::set(p3, false); GPIO::set(p4, false);
}
//Here we have the step setup, it's basically a rotating signal going from left to right in 8 steps.
void Motor::moveone(const bool &reversed) {
	if (step == 0) {
		//1 0 0 0
		GPIO::set(p1, true); GPIO::set(p2, false); GPIO::set(p3, false); GPIO::set(p4, false);
	} else if (step == 1) {
		//1 1 0 0
		GPIO::set(p1, true); GPIO::set(p2, true); GPIO::set(p3, false); GPIO::set(p4, false);
	} else if (step == 2) {
		//0 1 0 0
		GPIO::set(p1, false); GPIO::set(p2, true); GPIO::set(p3, false); GPIO::set(p4, false);
	} else if (step == 3) {
		//0 1 1 0
		GPIO::set(p1, false); GPIO::set(p2, true); GPIO::set(p3, true); GPIO::set(p4, false);
	} else if (step == 4) {
		//0 0 1 0
		GPIO::set(p1, false); GPIO::set(p2, false); GPIO::set(p3, true); GPIO::set(p4, false);
	} else if (step == 5) {
		//0 0 1 1
		GPIO::set(p1, false); GPIO::set(p2, false); GPIO::set(p3, true); GPIO::set(p4, true);
	} else if (step == 6) {
		//0 0 0 1
		GPIO::set(p1, false); GPIO::set(p2, false); GPIO::set(p3, false); GPIO::set(p4, true);
	} else if (step == 7) {
		//1 0 0 1
		GPIO::set(p1, true); GPIO::set(p2, false); GPIO::set(p3, false); GPIO::set(p4, true);
	}
	if(reversed) step--;
	else step++;

	if (step >= 8) step = 0;
	if (step < 0) step = 7;
}