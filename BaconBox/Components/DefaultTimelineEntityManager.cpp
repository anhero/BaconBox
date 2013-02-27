#include "DefaultTimelineEntityManager.h"

#include "BaconBox/Core/Entity.h"
#include "BaconBox/Components/Transform.h"
#include "BaconBox/Helper/Vector2ChangedData.h"

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
		return NULL;
//		return new DefaultTimelineEntityManager(*this);
	}
	
	void DefaultTimelineEntityManager::receiveMessage(int senderID, int destID, int message, void *data) {
		if (destID == Entity::BROADCAST) {
			if (message == Transform::MESSAGE_POSITION_CHANGED) {
				// We get the position changed data.
				Vector2ChangedData newPosition(*reinterpret_cast<Vector2ChangedData *>(data));
				// We calculate how much the entity moved.
				Vector2 delta = newPosition.newValue - newPosition.oldValue;
				
				// We declare variables we're gonna need in the loop.
				Vector2 tmpPosition;
				Entity *tmpEntity;
				
				for (ChildMap::iterator i = this->children.begin(); i != this->children.end(); ++i) {
					// We get the entity to move.
					tmpEntity = i->second[this->currentFrame];
					// We get the entity's position.
					tmpEntity->sendMessage(DefaultTimelineEntityManager::ID, Transform::ID, Transform::MESSAGE_GET_POSITION, &tmpPosition);
					// We calculate the new position.
					tmpPosition += delta;
					// We apply the new position.
					i->second[this->currentFrame]->sendMessage(DefaultTimelineEntityManager::ID, Transform::ID, Transform::MESSAGE_SET_POSITION, &tmpPosition);
				}
			} else if (message == Transform::MESSAGE_ROTATION_CHANGED) {
			}
		}
	}
	
	void DefaultTimelineEntityManager::update() {
		this->TimelineEntityManager::update();
		
		for (ChildMap::iterator i = this->children.begin(); i != this->children.end(); ++i) {
			i->second[this->currentFrame]->update();
		}
	}
	
	void DefaultTimelineEntityManager::render() {
		this->TimelineEntityManager::render();
		
		for (ChildMap::iterator i = this->children.begin(); i != this->children.end(); ++i) {
			i->second[this->currentFrame]->render();
		}
	}
}
