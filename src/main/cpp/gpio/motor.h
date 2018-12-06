#pragma once
#include <queue>

namespace distanceunits {
	constexpr long double operator "" dm(long double dm) { return dm * 10; }
	constexpr long double operator "" cm(long double cm) { return cm; }
}
class Motor {
private:
	int p1, p2, p3, p4; //The 4 ports to which the motor is attached
	Motor *mimic;

public:
	Motor(const int &port1, const int &port2, const int &port3, const int &port4);
	void move(const long double &millimeters);
	void setmimic(Motor *mimi);
};