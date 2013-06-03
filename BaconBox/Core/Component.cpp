#include "Component.h"

#include <algorithm>

#include "BaconBox/Core/Entity.h"
#include "BaconBox/Helper/DeleteHelper.h"
#include "BaconBox/Components/IComponentConnection.h"
#include "BaconBox/Components/ComponentAddedData.h"

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
		if (destID == Entity::BROADCAST) {
			if (message == Entity::MESSAGE_ADD_COMPONENT) {
				for (std::vector<IComponentConnection *>::iterator i = this->connections.begin(); i != this->connections.end(); ++i) {
					(*i)->componentAdded(*reinterpret_cast<ComponentAddedData *>(data));
				}
			} else if (message == Entity::MESSAGE_REMOVE_COMPONENT) {
				for (std::vector<IComponentConnection *>::iterator i = this->connections.begin(); i != this->connections.end(); ++i) {
					(*i)->componentRemoved(*reinterpret_cast<int*>(data));
				}
			}
		}
	}
	
	void Component::update() {
	}
	
	const std::string &Component::getComponentName() const {
		return IDManager::getName(this->getID());
	}
	
	Entity * Component::getEntity() const {
	    return this->entity;
	}
	
	void Component::setEntity(Entity *newEntity) {
		this->entity = newEntity;
		this->refreshConnections();
	}
	
	void Component::refreshConnections() {
		if (this->entity) {
			for (std::vector<IComponentConnection *>::iterator i = this->connections.begin(); i != this->connections.end(); ++i) {
				(*i)->refreshConnection(this->entity);
			}
		}
	}
	
	void Component::addConnection(IComponentConnection *newConnection) {
		this->connections.push_back(newConnection);
	}
	
	ComponentProxy::ComponentProxy(Entity* newEntity, Component * newComponent){
	    entity = newEntity;
	    if (newComponent) {
			component = newComponent;
			entity->addComponent(component);
	    }
	}
	
}