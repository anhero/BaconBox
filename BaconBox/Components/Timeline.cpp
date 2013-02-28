#include "Timeline.h"

namespace BaconBox {
	Timeline::Timeline() : Component() {
	}
	
	Timeline::Timeline(const Timeline &src) : Component(src) {
	}
	
	Timeline::~Timeline() {
	}
	
	void Timeline::receiveMessage(int senderID, int destID, int message, void *data) {
	}
}
