#pragma once
#include <queue>

namespace distanceunits {
	constexpr long double operator "" dm(long double dm) { return dm * 10; }
	constexpr long double operator "" cm(long double cm) { return cm; }
}

struct QueuedAction {
	long double centimeters;
	Motor *m;

	QueuedAction(const long double &centi, Motor *m_) { centimeters = centi; m = m_; }
};

class Motor {
private:
	int p1, p2, p3, p4; //The 4 ports to which the motor is attached
	Motor *mimic;
	void move(const long double &centimeters);
	static std::queue<QueuedAction> actions;

public:
	Motor(const int &port1, const int &port2, const int &port3, const int &port4);
	static void setup();
	void queue(const long double &centimeters);
	void setmimic(Motor *mimi);
};