#include "../pch.h"

std::queue<QueuedAction> Biker::actions;

void Biker::setup() {
	Logger::info("[BIKER] Starting Biker thread.");
	while (true) { //I'm too lazy to make this secure, safe, efficient or anything, don't judge.
		if (!actions.empty()) {
			//Logger::info("[BIKER] Executing action..");
			//QueuedAction qa = actions.front();
			//qa.m->moveint(qa.centimeters);
			//actions.pop();
		}
	}
}

void Biker::push(QueuedAction qa) {
	Logger::info("[BIKER] Executing action..");
	QueuedAction qa = actions.front();
	qa.m->moveint(qa.centimeters);
	actions.pop();
}