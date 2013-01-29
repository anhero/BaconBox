#include "State.h"

#include "BaconBox/Display/Camera.h"
#include "BaconBox/Components/EntityManager.h"
#include "BaconBox/Core/IDManager.h"
#include "BaconBox/PlatformFlagger.h"

#ifdef BB_FLASH_PLATEFORM
#include "BaconBox/Components/Flash/FlashEntityManager.h"
#endif
namespace BaconBox {
	const std::string State::DEFAULT_NAME = "State";
	const int State::MESSAGE_ADDED_ENTITY = IDManager::getID();
	const int State::MESSAGE_REMOVED_ENTITY = IDManager::getID();
	const int State::MESSAGE_GET_FOCUS = IDManager::getID();
	const int State::MESSAGE_LOSE_FOCUS = IDManager::getID();	
	int State::ID = IDManager::getID();


	State::State(const std::string &newName) : camera(new Camera()) {
		this->add(this->camera);
		setName(newName);
		addComponent(new EntityManager());
		
		#ifdef BB_FLASH_PLATEFORM
		addComponent(new FlashEntityManager());
		#endif
	}

	State::~State() {
	}

	void State::update() {
	    
	}

	void State::render() {
	    
	}
	
	void State::add(Entity *newEntity) {
	    sendMessage(State::ID, Entity::BROADCAST, State::MESSAGE_ADDED_ENTITY,  newEntity);
	}
	
	void State::remove(Entity *newEntity) {
	    if (newEntity && newEntity != this->camera) {
		sendMessage(State::ID, Entity::BROADCAST, State::MESSAGE_ADDED_ENTITY,  newEntity);
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
		Entity::update();
		this->update();
	}

	void State::internalRender() {
		Entity::render();
		this->render();
	}

	void State::internalOnGetFocus() {
		onGetFocus();
		sendMessage(State::ID, Entity::BROADCAST, State::MESSAGE_GET_FOCUS,  NULL);
	}

	void State::internalOnLoseFocus() {
		onLoseFocus();
		sendMessage(State::ID, Entity::BROADCAST, State::MESSAGE_LOSE_FOCUS,  NULL);
	}
}
