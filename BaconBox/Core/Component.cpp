#include "Component.h"

#include <algorithm>

#include "BaconBox/Core/Entity.h"
#include "BaconBox/Helper/DeleteHelper.h"
#include "BaconBox/Helper/IComponentConnection.h"

namespace BaconBox {
    
	BB_ID_IMPL(Component);
	
	Component::Component() : entity(NULL), sigly::HasSlots<>() {
	}
	
	Component::Component(const Component &src) : entity(NULL) {
	}
	
	Component::~Component() {
		std::for_each(this->connections.begin(), this->connections.end(), DeletePointerDirect());
	}
	
	Component &Component::operator=(const Component &src) {
		return *this;
	}
	
	Component *Component::clone() const {
		return new Component(*this);
	}
	
	void Component::sendMessage(int destID, int message, void *data) {
		if (entity) {
			entity->sendMessage(this->getID(), destID, message, data);
		}
	}

	void Component::receiveMessage(int senderID, int destID, int message, void *data) {
		for (std::vector<IComponentConnection *>::iterator i = this->connections.begin(); i != this->connections.end(); ++i) {
			(*i)->receiveMessage(message, data);
		}
	}
	
	void Component::update() {
	}
	
	void Component::render() {
	}

	const std::string &Component::getComponentName() const {
		return IDManager::getName(this->getID());
	}
	
	Entity *Component::getEntity() const {
		return this->entity;
	}
	
	void Component::addConnection(IComponentConnection *newConnection) {
		this->connections.push_back(newConnection);
	}
	
	ComponentProxy::ComponentProxy(Entity* entity, Component * component){
	    this->entity = entity;
	    if(component){
		this->component = component;
		entity->addComponent(component);
	    }
	}
	
}