#include "Component.h"

#include "Entity.h"

namespace BaconBox {
    
	BB_ID_IMPL(Component);
	
	Component::Component() : entity(NULL), sigly::HasSlots<>() {
	}
	
	Component::Component(const Component &src) : entity(NULL) {
	}
	
	Component::~Component() {
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
	}
	
	void Component::update() {
	}
	
	void Component::render() {
	}

	std::string Component::getComponentName() const {
		return IDManager::getName(this->getID());
	}
	
	Entity *Component::getEntity() const {
		return this->entity;
	}
	
	ComponentProxy::ComponentProxy(Entity* entity, Component * component){
	    this->entity = entity;
	    if(component){
		this->component = component;
		entity->addComponent(component);
	    }
	}
	
}