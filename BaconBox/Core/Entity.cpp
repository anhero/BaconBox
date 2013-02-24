#include "Entity.h"

#include <algorithm>

#include "BaconBox/Core/IDManager.h"
#include "BaconBox/Console.h"

namespace BaconBox {
	BB_ID_IMPL(Entity);
	
	int Entity::BROADCAST = IDManager::generatetID();

	Entity::Entity() : components(), parent(NULL), sigly::HasSlots<>() {
	}

	Entity::Entity(const Entity &src) : components(), parent(NULL) {
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


	Component * Entity::addComponent(Component *newComponent) {
		components.push_back(newComponent);
		newComponent->entity = this;
		return newComponent;
	}

	void Entity::removeComponentAt(std::vector<Component *>::size_type index) {
		if (index < components.size()) {
			delete components[index];
			components.erase(components.begin() + index);
		}
	}

	void Entity::removeComponent(Component *component) {
		std::vector<Component *>::iterator found = std::find(this->components.begin(), this->components.end(), component);

		if (found != this->components.end()) {
			delete *found;
			this->components.erase(found);
		}
	}

	void Entity::removeComponents(int id) {
		std::vector<Component *>::size_type i = 0;

		while (i < this->components.size()) {
			if (this->components[i]->getID() == id) {
				delete this->components[i];
				this->components.erase(this->components.begin() + i);

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
	
	Component *Entity::getComponent(int id) const {
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
		if(!result){
		    Console__error("Can't find the requested component in the given entity.: ID" << id << " name: " << IDManager::getName(id));
		}
		return result;
	}
	
	const Entity *Entity::getParent() const {
		return this->parent;
	}
	
	Entity *Entity::getParent() {
		return this->parent;
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
			tmpComponent->entity = this;
			this->components.push_back(tmpComponent);
		}
	}
}
