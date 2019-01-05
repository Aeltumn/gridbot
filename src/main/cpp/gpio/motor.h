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
	bool hasMimic, hasMirror;
	int step = 0;

public:
	Motor(const int &port1, const int &port2, const int &port3, const int &port4);
	void queue(const long double &centimeters);
	void setmimic(Motor *mimi);
	void setmirror(Motor *mirror);
	void moveint(const long double &centimeters);
	void moveone(const bool &reversed);
};

struct QueuedAction {
	long double centimeters;
	Motor *m;

	QueuedAction(const long double &centi, Motor *m_) { centimeters = centi; m = m_; }
};
