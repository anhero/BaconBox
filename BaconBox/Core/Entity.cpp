#include "Entity.h"

#include "Component.h"

namespace BaconBox {
	void Entity::sendMessage(int id, int message, void *data) {
		for (std::vector<Component *>::iterator i = this->components.begin(); i != this->components.end(); ++i) {
			(*i)->receiveMessage(id, message, data);
		}
	}
	
	const std::string &Entity::getName() const {
		return this->name;
	}
	
	void Entity::setName(const std::string &newName) {
		this->name = newName;
	}
	
	const std::vector<Component *> &Entity::getComponents() const {
		return components;
	}
	
	void Entity::addComponent(Component *newComponent) {
		components.push_back(newComponent);
		newComponent->entity = this;
	}
	
	void Entity::removeComponentAt(std::vector<Component *>::size_type index) {
		components[index]->entity = NULL;
		components.erase(components.begin() + index);
	}
	
	void Entity::removeComponent(Component *component) {
		std::vector<Component *>::iterator i = this->components.begin();
		
		while (i != this->components.end()) {
			if ((*i) == component) {
				(*i)->entity = NULL;
				this->components.erase(i);
				return;
			} else {
				++i;
			}
		}
	}
	
	void Entity::removeComponents(int id) {
		std::vector<Component *>::size_type i = 0;
		
		while (i < this->components.size()) {
			if (this->components[i]->getId() == id) {
				this->components[i]->entity = NULL;
				this->components.erase(this->components.begin() + i);
			} else {
				++i;
			}
		}
	}
	
	const std::vector<Entity *> &Entity::getChildren() const {
		return this->children;
	}
	
	void Entity::addChild(Entity *newChild) {
		this->children.push_back(newChild);
		newChild->parent = this;
	}
	
	void Entity::removeChildAt(std::vector<Entity *>::size_type index) {
		this->children[index]->parent = NULL;
		this->children.erase(this->children.begin() + index);
	}
	
	void Entity::removeChild(Entity *child) {
		std::vector<Entity *>::iterator i = this->children.begin();
		
		while (i != this->children.end()) {
			if (*i == child) {
				(*i)->parent = NULL;
				this->children.erase(i);
				
				return;
			} else {
				++i;
			}
		}
	}
}