#pragma once
#include <queue>
#include "motor.h"

class Biker {
private:
	static std::queue<QueuedAction> actions;

public:
	static void setup();
	static void push(QueuedAction ac);
};
