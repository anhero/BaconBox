#include "DefaultEntityContainer.h"

namespace BaconBox {
	DefaultEntityContainer::DefaultEntityContainer() : Component() {
	}
	
	DefaultEntityContainer::DefaultEntityContainer(const DefaultEntityContainer &src) : Component(src) {
	}
	
	DefaultEntityContainer::~DefaultEntityContainer() {
	}
	
	DefaultEntityContainer &DefaultEntityContainer::operator=(const DefaultEntityContainer &src) {
		if (this != &src) {
		}
		
		return *this;
	}
	
	DefaultEntityContainer *DefaultEntityContainer::clone() const {
		return new DefaultEntityContainer(*this);
	}
	
	void DefaultEntityContainer::receiveMessage(int senderID, int destID, int message, void *data) {
	}
}
