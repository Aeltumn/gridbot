#include "pch.h"

std::queue<QueuedAction> Biker::actions;

void Biker::setup() {
	try {
		Logger::info("[BIKER] Starting Biker thread.");
		while (true) {
			if (!actions.empty()) {
				QueuedAction qa = actions.front();
				if (qa.centimeters == 0) {
					char buf[256];
					buf[0] = 0;
					strcat(buf, "[BIKER] Executing action, setting magnet to ");
					strcat(buf, std::to_string(qa.magnet).c_str());
					strcat(buf, "...");
					Logger::info(buf);
					GPIO::set(10, qa.magnet);
					actions.pop();
					continue;
				}
				char buf[256];
				buf[0] = 0;
				strcat(buf, "[BIKER] Executing action, moving ");
				strcat(buf, std::to_string(qa.centimeters).c_str());
				strcat(buf, " centimetres...");
				Logger::info(buf);
				qa.m->move(qa.centimeters);
				actions.pop();
			}
		}
	} catch (const std::exception& e) {
		Logger::info(e.what());
		return;
	}
}

void Biker::push(QueuedAction qa) { actions.push(qa); }