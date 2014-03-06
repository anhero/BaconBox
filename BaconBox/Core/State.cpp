#include "State.h"

#include "BaconBox/Display/Camera.h"
#include "BaconBox/Components/EntityManager.h"
#include "BaconBox/Core/IDManager.h"
#include "BaconBox/PlatformFlagger.h"

#ifdef BB_FLASH_PLATFORM
#include "BaconBox/Components/Flash/FlashEntityManager.h"
#include "BaconBox/Components/Flash/FlashCameraManager.h"
#endif

#include "BaconBox/Console.h"

#ifdef BB_LUA
#include "BaconBox/Helper/Lua/LuaHelper.h"
#endif //BB_LUA

namespace BaconBox {
	BB_ID_IMPL(State);
	
	const std::string State::DEFAULT_NAME = "State";
	const int State::MESSAGE_ADDED_ENTITY = IDManager::generateID("State::MESSAGE_ADDED_ENTITY");
	const int State::MESSAGE_REMOVED_ENTITY = IDManager::generateID("State::MESSAGE_REMOVED_ENTITY");
	const int State::MESSAGE_GET_FOCUS = IDManager::generateID("State::MESSAGE_GET_FOCUS");
	const int State::MESSAGE_LOST_FOCUS = IDManager::generateID("State::MESSAGE_LOST_FOCUS");

	State::State(const std::string &newName) : Entity(), HasNameProxy(this, newName), UIManagerProxy(this)
	#ifdef BB_LUA
	, LuaEntityProxy(this)
	#endif //BB_LUA
	{
		camera = new Camera();
		addComponent(new EntityManager());
		this->add(this->camera);


		#ifdef BB_FLASH_PLATFORM
            FlashEntityManager * fm = new FlashEntityManager();
            addComponent(fm);
            this->camera->getComponent<FlashCameraManager>()->setEntityManager(fm);
		#endif


	}

	State::~State() {
	}


	void State::update() {

	}

	Entity * State::add(Entity *newEntity) {
	    sendMessage(State::ID, Entity::BROADCAST, State::MESSAGE_ADDED_ENTITY,  newEntity);
		return newEntity;
	}
	
#ifdef BB_LUA
	Entity * State::add(lua_State * L){
		return add(LuaHelper::getEntityFromLuaEntity(L));
	}
#endif //BB_LUA

	void State::remove(Entity *newEntity) {
	    if (newEntity && newEntity != this->camera) {
		sendMessage(State::ID, Entity::BROADCAST, State::MESSAGE_REMOVED_ENTITY,  newEntity);
	    }
	}
	
#ifdef BB_LUA
	void State::remove(lua_State * L){
		remove(LuaHelper::getEntityFromLuaEntity(L));
	}
#endif //BB_LUA

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


	void State::internalOnGetFocus() {
		onGetFocus();
		sendMessage(State::ID, Entity::BROADCAST, State::MESSAGE_GET_FOCUS,  NULL);
	}

	void State::internalOnLoseFocus() {
		onLoseFocus();
		sendMessage(State::ID, Entity::BROADCAST, State::MESSAGE_LOST_FOCUS,  NULL);
	}
}
