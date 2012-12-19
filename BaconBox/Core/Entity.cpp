#include "Entity.h"

namespace BaconBox {
	Entity::Entity() : name(), components(), children(), parent(NULL) {
	}

	Entity::Entity(const Entity &src) : name(src.name), components(), children(), parent(NULL) {
		this->copyFrom(src);
	}

	Entity::~Entity() {
		this->free();
	}

	Entity &Entity::operator=(const Entity &src) {
		if (this != &src) {
			this->name = src.name;

			this->clear();
			
			this->copyFrom(src);
		}

		return *this;
	}

	Entity *Entity::clone() const {
		return new Entity(*this);
	}
	
	
	Component * Entity::getComponent(const std::string &componentName) const {
		Component *result = NULL;
		bool notFound = true;
		std::vector<Component *>::const_iterator i = this->components.begin();
		
		while (notFound && i != this->components.end()) {
			if ((*i)->getName() == componentName) {
				result = (*i);
				notFound = false;
			}
		}
		
		return result;
	}

	void Entity::sendMessage(int id, int message, void *data) {
		for (std::vector<Component *>::iterator i = this->components.begin(); i != this->components.end(); ++i) {
			(*i)->receiveMessage(id, message, data);
		}
	}

	void Entity::update() {
		for (std::vector<Component *>::iterator i = this->components.begin(); i != this->components.end(); ++i) {
			(*i)->update();
		}

		for (std::vector<Entity *>::iterator i = this->children.begin(); i != this->children.end(); ++i) {
			(*i)->update();
		}
	}

	void Entity::render() {
		for (std::vector<Component *>::iterator i = this->components.begin(); i != this->components.end(); ++i) {
			(*i)->render();
		}

		for (std::vector<Entity *>::iterator i = this->children.begin(); i != this->children.end(); ++i) {
			(*i)->render();
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

	void Entity::clear() {
		free();
		this->components.clear();
		this->children.clear();
	}

	void Entity::free() {
		for (std::vector<Component *>::iterator i = this->components.begin(); i != this->components.end(); ++i) {
			delete *i;
		}

		for (std::vector<Entity *>::iterator i = this->children.begin(); i != this->children.end(); ++i) {
			delete *i;
		}
	}
	
	void Entity::copyFrom(const Entity &src) {
		this->components.reserve(src.components.size());
		this->children.reserve(src.children.size());
		
		Component *tmpComponent;
		
		for (std::vector<Component *>::const_iterator i = src.components.begin(); i != src.components.end(); ++i) {
			tmpComponent = (*i)->clone();
			tmpComponent->entity = this;
			this->components.push_back(tmpComponent);
		}
		
		Entity *tmpEntity;
		
		for (std::vector<Entity *>::const_iterator i = src.children.begin(); i != src.children.end(); ++i) {
			tmpEntity = (*i)->clone();
			tmpEntity->parent = this;
			this->children.push_back(tmpEntity);
		}
	}
}