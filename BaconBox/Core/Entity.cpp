#include "Entity.h"

#include "Component.h"

namespace BaconBox {
	void Entity::sendMessage(int id, int message, void *data) {
		for (std::vector<Component *>::iterator i = components.begin(); i != components.end(); ++i) {
			(*i)->receiveMessage(id, message, data);
		}
	}
}