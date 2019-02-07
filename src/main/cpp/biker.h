#pragma once
#include <queue>
#include "motor.h"

class Biker {
private:
	static const long ID = 156484; //The Biker's ID, the Motor will only accept movements from this ID.
	static std::queue<QueuedAction> actions;

public:
	static void setup();
	static void push(QueuedAction ac);
};
