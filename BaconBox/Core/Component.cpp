#include "Component.h"

#include "Entity.h"

namespace BaconBox {
	void Component::sendMessage(int message, void *data) {
		if (entity) {
			entity->sendMessage(this->getId(), message, data);
		}
	}

	void Component::receiveMessage(int id, int message, void *data) {
	}

	const std::string &Component::getName() const {
		return this->name;
	}
	
	void Component::setName(const std::string &newName) {
		this->name = newName;
	}
}