#include "DefaultTimelineEntityManager.h"

namespace BaconBox {
	DefaultTimelineEntityManager::DefaultTimelineEntityManager() : TimelineEntityManager() {
	}
	
	DefaultTimelineEntityManager::DefaultTimelineEntityManager(const DefaultTimelineEntityManager &src) : TimelineEntityManager(src) {
	}
	
	DefaultTimelineEntityManager::~DefaultTimelineEntityManager() {
	}
	
	DefaultTimelineEntityManager &DefaultTimelineEntityManager::operator=(const DefaultTimelineEntityManager &src) {
		if (this != &src) {
		}
		
		return *this;
	}
	
	DefaultTimelineEntityManager *DefaultTimelineEntityManager::clone() const {
		return new DefaultTimelineEntityManager(*this);
	}
	
	void DefaultTimelineEntityManager::receiveMessage(int senderID, int destID, int message, void *data) {
	}
	
	void DefaultTimelineEntityManager::update() {
	}
	
	void DefaultTimelineEntityManager::render() {
	}
}
