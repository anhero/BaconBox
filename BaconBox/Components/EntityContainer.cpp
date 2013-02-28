#include "EntityContainer.h"

namespace BaconBox {
	EntityContainer::EntityContainer() : Component() {
	}
	
	EntityContainer::EntityContainer(const EntityContainer &src) : Component(src) {
	}
	
	EntityContainer::~EntityContainer() {
	}
	
	void EntityContainer::receiveMessage(int senderID, int destID, int message, void *data) {
	}
}
