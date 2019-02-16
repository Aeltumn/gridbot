#pragma once

namespace distanceunits {
	constexpr long double operator "" dm(long double dm) { return dm * 10; }
	constexpr long double operator "" cm(long double cm) { return cm; }
}

class Motor {
private:
	int p1, p2, p3, p4; //The 4 ports to which the motor is attached
	Motor *mimic; // Same direction
	Motor *mirror; // Opposite direction
	bool hasMimic = false, hasMirror = false; //storage booleans to see if we've set a mimic or mirror, checking if the point was zero was failing
	int step = 0;

	void moveint(const long double &centimeters);
	void moveone(const bool &reversed);

public:
	Motor(const int &port1, const int &port2, const int &port3, const int &port4);
	void queue(const long double &centimeters);
	void move(const long double &centimeters);
	void setmimic(Motor *mimi);
	void setmirror(Motor *mirror);
};

//A queued action is as it says, an action in the queue, it stores which motor and how many centimeters to move. The biker handles and consequently removes the QueuedAction.
struct QueuedAction {
	long double centimeters;
	Motor *m;
	bool magnet;
	bool isMagnet = false;

	QueuedAction(const long double &centi, Motor *m_) { centimeters = centi; m = m_; isMagnet = false; }
	QueuedAction(const bool &magnet_) { magnet = magnet_; isMagnet = true; }
};
