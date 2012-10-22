#include "BaconBox/State.h"

#include "Entity.h"

namespace BaconBox {
	const std::string State::DEFAULT_NAME = "State";

	State::State(const std::string &newName) : name(newName), entities() {
	}

	State::~State() {
	}

	void State::update() {
	}

	void State::render() {
	}

	const std::string &State::getName() const {
		return name;
	}

	void State::setName(const std::string &newName) {
		name = newName;
	}
	
	void State::add(Entity *newEntity) {
		if (newEntity) {
			this->entities.push_back(newEntity);
		}
	}

	void State::onGetFocus() {
	}

	void State::onLoseFocus() {
	}

	void State::internalUpdate() {
		for (std::vector<Entity *>::iterator i = this->entities.begin(); i != this->entities.end(); ++i) {
			(*i)->update();
		}
		this->update();
	}

	void State::internalRender() {
		for (std::vector<Entity *>::iterator i = this->entities.begin(); i != this->entities.end(); ++i) {
			(*i)->render();
		}
		this->render();
	}

	void State::internalOnGetFocus() {
		onGetFocus();
	}

	void State::internalOnLoseFocus() {
		onLoseFocus();
	}
}
