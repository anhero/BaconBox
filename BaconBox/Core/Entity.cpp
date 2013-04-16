#include "Entity.h"

#include <algorithm>

#include "BaconBox/Core/IDManager.h"
#include "BaconBox/Console.h"
#include "BaconBox/Components/ComponentAddedData.h"

namespace BaconBox {
	BB_ID_IMPL(Entity);
	
	int Entity::BROADCAST = IDManager::generateID();
	
	int Entity::MESSAGE_ADD_COMPONENT = IDManager::generateID();
	int Entity::MESSAGE_REMOVE_COMPONENT = IDManager::generateID();

	Entity::Entity() : components(), sigly::HasSlots<>() {
	}

	Entity::Entity(const Entity &src) : components() {
		this->copyFrom(src);
	}

	Entity::~Entity() {
		this->free();
	}

	Entity &Entity::operator=(const Entity &src) {
		if (this != &src) {
			this->clear();

			this->copyFrom(src);
		}

		return *this;
	}

	Entity *Entity::clone() const {
		return new Entity(*this);
	}

	void Entity::sendMessage(int senderID, int destID, int message, void *data) {
		for (std::vector<Component *>::iterator i = this->components.begin(); i != this->components.end(); ++i) {
			(*i)->receiveMessage(senderID, destID, message, data);
		}
	}

	void Entity::update() {
		for (std::vector<Component *>::iterator i = this->components.begin(); i != this->components.end(); ++i) {
			(*i)->update();
		}
	}

	void Entity::render() {
		for (std::vector<Component *>::iterator i = this->components.begin(); i != this->components.end(); ++i) {
			(*i)->render();
		}
	}

	const std::string &Entity::getEntityName() const {
		return IDManager::getName(this->getID());
	}


	const std::vector<Component *> &Entity::getComponents() const {
		return components;
	}
	
	void Entity::printComponentsName(){
	    for(std::vector<Component *>::iterator i = components.begin(); i != components.end(); i++){
		std::cout << " Entity: " << IDManager::getName(this->getID()) << " Component: " << IDManager::getName((*i)->getID()) << std::endl;
	    }
	}


	Component *Entity::addComponent(Component *newComponent) {
		components.push_back(newComponent);
		newComponent->setEntity(this);
		
		ComponentAddedData data(newComponent->getID(), newComponent);
		
		this->sendMessage(Entity::ID, BROADCAST, MESSAGE_ADD_COMPONENT, &data);
		
		return newComponent;
	}

	void Entity::removeComponentAt(std::vector<Component *>::size_type index) {
		if (index < components.size()) {
			Component *toRemove = this->components[index];
			
			this->components.erase(components.begin() + index);
			
			int componentId = toRemove->getID();
			
			this->sendMessage(Entity::ID, BROADCAST, MESSAGE_REMOVE_COMPONENT, &componentId);
			
			delete toRemove;
		}
	}

	void Entity::removeComponent(Component *component) {
		std::vector<Component *>::iterator found = std::find(this->components.begin(), this->components.end(), component);

		if (found != this->components.end()) {
			Component *toRemove = *found;
			
			this->components.erase(found);
			
			int componentId = toRemove->getID();
			
			this->sendMessage(Entity::ID, BROADCAST, MESSAGE_REMOVE_COMPONENT, &componentId);
			
			delete toRemove;
		}
	}

	void Entity::removeComponents(int id) {
		std::vector<Component *>::size_type i = 0;

		while (i < this->components.size()) {
			if (this->components[i]->getID() == id) {
				Component *toRemove = this->components[i];
				
				this->components.erase(this->components.begin() + i);
				
				int componentId = toRemove->getID();
				
				this->sendMessage(Entity::ID, BROADCAST, MESSAGE_REMOVE_COMPONENT, &componentId);
				
				delete toRemove;
			} else {
				++i;
			}
		}
	}

	void Entity::clear() {
		free();
		this->components.clear();
	}
	
	Component *Entity::getComponent(const std::string &componentName) const {
		int id = IDManager::getID(componentName);
		return getComponent(id);
	}
	
	Component *Entity::getComponent(int id,  bool noPrint) const {
		Component *result = NULL;
		bool notFound = true;
		std::vector<Component *>::const_iterator i = this->components.begin();
		
		while (notFound && i != this->components.end()) {
			if ((*i)->getID() == id) {
				result = (*i);
				notFound = false;
				
			} else {
				i++;
			}
		}
		if(!noPrint && !result){
		    Console__error("Can't find the requested component in the given entity.: ID" << id << " name: " << IDManager::getName(id));
		}
		return result;
	}
	


	void Entity::free() {
		for (std::vector<Component *>::iterator i = this->components.begin(); i != this->components.end(); ++i) {
			delete *i;
		}
	}

	void Entity::copyFrom(const Entity &src) {
		this->components.reserve(src.components.size());

		Component *tmpComponent;

		for (std::vector<Component *>::const_iterator i = src.components.begin(); i != src.components.end(); ++i) {
			tmpComponent = (*i)->clone();
			tmpComponent->setEntity(this);
			this->components.push_back(tmpComponent);
		}
	}
}
