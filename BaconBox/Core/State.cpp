#include "State.h"

#include "BaconBox/Display/Camera.h"
#include "BaconBox/Components/EntityManager.h"
#include "BaconBox/Core/IDManager.h"
#include "BaconBox/PlatformFlagger.h"

#ifdef BB_FLASH_PLATEFORM
#include "BaconBox/Components/Flash/FlashEntityManager.h"
#endif

#include "BaconBox/Console.h"

namespace BaconBox {
	BB_ID_IMPL(State);
	
	const std::string State::DEFAULT_NAME = "State";
	const int State::MESSAGE_ADDED_ENTITY = IDManager::generatetID("State::MESSAGE_ADDED_ENTITY");
	const int State::MESSAGE_REMOVED_ENTITY = IDManager::generatetID("State::MESSAGE_REMOVED_ENTITY");
	const int State::MESSAGE_GET_FOCUS = IDManager::generatetID("State::MESSAGE_GET_FOCUS");
	const int State::MESSAGE_LOSE_FOCUS = IDManager::generatetID("State::MESSAGE_LOSE_FOCUS");	

	State::State(const std::string &newName) : camera(new Camera()), HasNameProxy(this, newName)
	#ifdef BB_LUA
	, LuaStateProxy(this) 
	#endif //BB_LUA
	{
		addComponent(new EntityManager());
		this->add(this->camera);
		
		this->add(this->camera);
		
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
