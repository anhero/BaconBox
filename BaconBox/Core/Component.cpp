#include "Component.h"

#include "Entity.h"

namespace BaconBox {
	Component::Component() : name(), entity(NULL) {
	}
	
	Component::Component(const Component &src) : name(src.name), entity(NULL) {
	}
	
	Component::~Component() {
	}
	
	Component &Component::operator=(const Component &src) {
		if (this != &src)
		{
			this->name = src.name;
		}
		
		return *this;
	}
	
	Component *Component::clone() const {
		return new Component(*this);
	}
	
	void Component::sendMessage(int message, void *data) {
		if (entity) {
			entity->sendMessage(this->getId(), message, data);
		}
	}

	void Component::receiveMessage(int id, int message, void *data) {
	}
	
	void Component::update() {
	}
	
	void Component::render() {
	}

	const std::string &Component::getName() const {
		return this->name;
	}
	
	void Component::setName(const std::string &newName) {
		this->name = newName;
	}
}