#include "Entity.h"
#include "BaconBox/Core/IDManager.h"
#include "BaconBox/Console.h"
namespace BaconBox {
	BB_ID_IMPL(Entity);
	
	int Entity::BROADCAST = IDManager::getID();

	Entity::Entity() : name(), components(), parent(NULL) {
	}

	Entity::Entity(const Entity &src) : name(src.name), components(), parent(NULL) {
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


	Component *Entity::getComponent(const std::string &componentName) const {
		Component *result = NULL;
		bool notFound = true;
		std::vector<Component *>::const_iterator i = this->components.begin();

		while (notFound && i != this->components.end()) {
			if ((*i)->getName() == componentName) {
				result = (*i);
				notFound = false;

			} else {
				i++;
			}
		}
		if(!result)Console::error("Can't find the requested component in the given entity");
		return result;
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
		if(!result)Console::error("Can't find the requested component in the given entity. Maybe you haven't implemented BB_ID_HEADER and BB_ID_IMPL.");
		return result;
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
			if (this->components[i]->getID() == id) {
				this->components[i]->entity = NULL;
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
