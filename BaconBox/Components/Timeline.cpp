#include "Timeline.h"

namespace BaconBox {
	int Timeline::MESSAGE_NB_FRAMES_CHANGED = IDManager::generateID();
	
	Timeline::Timeline() : Component() {
	}
	
	Timeline::Timeline(const Timeline &src) : Component(src) {
	}
	
	Timeline::~Timeline() {
	}
	
	void Timeline::receiveMessage(int senderID, int destID, int message, void *data) {
	}
}
