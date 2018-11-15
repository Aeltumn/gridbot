#ifndef MOTOR_H_
#define MOTOR_H_

namespace distanceunits {
	constexpr long double operator "" dm(long double dm);
	constexpr long double operator "" cm(long double cm);
	constexpr long double operator "" mm(long double mm);
}
enum Axis {X, Y};
class Motor {
private:
	int p1, p2, p3, p4; //The 4 ports to which the motor is attached

public:
	Motor(const int &port1, const int &port2, const int &port3, const int &port4);
	void move(const Axis &ax, const long double &millimeters);
};
#endif