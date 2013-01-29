
#include "BaconBox/Core/IDManager.h"
#include "BaconBox/core/Component.h"
#include "BaconBox/Components/Flash/MovieClipHolder.h"
#include "BaconBox/Components/Flash/FlashEntityManager.h"
#include "BaconBox/Core/State.h"
#include "BaconBox/Helper/Flash/FlashHelper.h"

namespace BaconBox {
	int FlashEntityManager::ID = IDManager::getID();
	
	FlashEntityManager::FlashEntityManager() : Component() {
	    setName("FlashEntityManager");
	    movieClipManager = FlashHelper::construct("flash.display.MovieClip");
	   	AS3::local::internal::trace(movieClipManager);

	}

	AS3::local::var FlashEntityManager::getMovieCLip(){
		return movieClipManager;
	}

	FlashEntityManager::~FlashEntityManager() {
	}
		
	void FlashEntityManager::add(Entity *newEntity) {
	    if(newEntity){
	    	AS3::local::var mc = reinterpret_cast<MovieClipHolder*>(newEntity->getComponent(MovieClipHolder::ID))->getMovieCLip();
	    	AS3::local::var args[1] = {mc};
	    	FlashHelper::callMethod(movieClipManager, "addChild", 1, args);
	    }
	}
	
	void FlashEntityManager::remove(Entity *newEntity) {
		if (newEntity) {
			AS3::local::var mc = reinterpret_cast<MovieClipHolder*>(newEntity->getComponent(MovieClipHolder::ID))->getMovieCLip();
	    	AS3::local::var args[1] = {mc};
	    	FlashHelper::callMethod(movieClipManager, "removeChild", 1, args);
		}
	}
	

	int FlashEntityManager::getID() const {
		return FlashEntityManager::ID;
	}

	void FlashEntityManager::receiveMessage(int senderID, int destID, int message, void *data) {
		if(senderID != State::ID)return;
		
		if(message == State::MESSAGE_ADDED_ENTITY){
		    add(static_cast<Entity*>(data));
		}
		else if(message == State::MESSAGE_REMOVED_ENTITY){
			remove(static_cast<Entity*>(data));
		}
		

	}
	
}