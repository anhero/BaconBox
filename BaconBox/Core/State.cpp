#include "BaconBox/State.h"

#include "Entity.h"
#include "Camera.h"

namespace BaconBox {
	const std::string State::DEFAULT_NAME = "State";

	State::State(const std::string &newName) : name(newName), entities(), toAdd(), toRemove(), camera(new Camera()) {
		this->add(this->camera);
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
			this->toAdd.push_back(newEntity);
		}
	}
	
	void State::remove(Entity *newEntity) {
		if (newEntity && newEntity != this->camera) {
			this->toRemove.insert(newEntity);
		}
	}
	
	Camera &State::getCamera() {
		return *this->camera;
	}
	
	const Camera &State::getCamera() const {
		return *this->camera;
	}

	void State::onGetFocus() {
	}

	void State::onLoseFocus() {
	}

	void State::internalUpdate() {
		// We add the entities.
		if (!this->toAdd.empty()) {
			this->entities.reserve(this->entities.size() + this->toAdd.size());
			
			
			for (std::list<Entity *>::iterator i = this->toAdd.begin(); i != this->toAdd.end(); ++i) {
				this->entities.push_back(*i);
			}
			
			this->toAdd.clear();
		}
		
		// We remove the entities.
		if (!this->toRemove.empty()) {
			std::vector<Entity *>::size_type i = 0;
			
			while (i < this->entities.size()) {
				if (this->toRemove.find(this->entities[i]) != this->toRemove.end()) {
					this->entities.erase(this->entities.begin() + i);
				} else {
					++i;
				}
			}
			
			this->toRemove.clear();
		}
		
		// We update the entities.
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
