#include "TimelineEntityManager.h"

namespace BaconBox {
	TimelineEntityManager::TimelineEntityManager() : Component() {
	}
	
	TimelineEntityManager::TimelineEntityManager(const TimelineEntityManager &src) : Component(src) {
	}
	
	TimelineEntityManager::~TimelineEntityManager() {
	}
	
	TimelineEntityManager &TimelineEntityManager::operator=(const TimelineEntityManager &src) {
		if (this != &src) {
		}
		
		return *this;
	}
	
	TimelineEntityManager *TimelineEntityManager::clone() const {
		return new TimelineEntityManager(*this);
	}
	
	void TimelineEntityManager::receiveMessage(int senderID, int destID, int message, void *data) {
	}
}
