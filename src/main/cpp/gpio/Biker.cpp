#include "../pch.h"

std::queue<QueuedAction> Biker::actions;

void Biker::setup() {
	try {
		Logger::info("[BIKER] Starting Biker thread.");
		bool isRunning = true;
		while (isRunning) { //I'm too lazy to make this secure, safe, efficient or anything, don't judge.
			if (!actions.empty()) {
				Logger::info("[BIKER] Executing action..");
				QueuedAction qa = actions.front();
				qa.m->moveint(qa.centimeters);
				actions.pop();
			}
		}
	} catch (const std::exception& e) {
		Logger::info(e.what());
		return;
	}
}

void Biker::push(QueuedAction qa) { actions.push(qa); }