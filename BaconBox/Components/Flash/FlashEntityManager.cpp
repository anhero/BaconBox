
#include "BaconBox/Core/IDManager.h"
#include "BaconBox/core/Component.h"
#include "BaconBox/Components/Flash/MovieClipHolder.h"
#include "BaconBox/Components/Flash/FlashEntityManager.h"
#include "BaconBox/Core/State.h"
#include "BaconBox/Helper/Flash/FlashHelper.h"
#include "BaconBox/Core/Engine.h"
#include "BaconBox/Core/Flash/FlashEngine.h"
#include "BaconBox/Console.h"
#include "BaconBox/Components/Flash/TextFieldHolder.h"

#include "BaconBox/Display/Text/TextEntity.h"
#include "BaconBox/MovieClipEntity/MovieClipEntity.h"

namespace BaconBox {
	
	BB_ID_IMPL(FlashEntityManager);

	FlashEntityManager::FlashEntityManager() : Component() {
	    movieClipManager = FlashHelper::construct("flash.display.MovieClip");

	}

	AS3::local::var FlashEntityManager::getMovieClip(){
		return movieClipManager;
	}

	FlashEntityManager::~FlashEntityManager() {
	}


	void FlashEntityManager::setProperty(const std::string & propertyName, AS3::local::var arg){
		FlashHelper::setProperty(movieClipManager, propertyName, arg);
	}

	AS3::local::var FlashEntityManager::getProperty(const std::string & propertyName){
		return FlashHelper::getProperty(movieClipManager, propertyName);
	}

	AS3::local::var FlashEntityManager::callMethod(const std::string & functionName, int argCount, AS3::local::var *args){
		return FlashHelper::callMethod(movieClipManager, functionName, argCount, args);
	} 

		
	void FlashEntityManager::add(Entity *newEntity) {
	    if(newEntity){
	    	AS3::local::var mc;
	    	if(newEntity->getID() == MovieClipEntity::ID){
	    		mc = reinterpret_cast<MovieClipHolder*>(newEntity->getComponent(MovieClipHolder::ID))->getMovieClip();
	    	}
	    	else if(newEntity->getID() == TextEntity::ID){
	    		mc = reinterpret_cast<TextFieldHolder*>(newEntity->getComponent(TextFieldHolder::ID))->getMovieClip();
	    	}
	    	AS3::local::var args[1] = {mc};
	    	FlashHelper::callMethod(movieClipManager, "addChild", 1, args);
	    }
	}
	
	void FlashEntityManager::remove(Entity *newEntity) {
		if (newEntity) {
			AS3::local::var mc;
	    	if(newEntity->getID() == MovieClipEntity::ID){
	    		mc = reinterpret_cast<MovieClipHolder*>(newEntity->getComponent(MovieClipHolder::ID))->getMovieClip();
	    	}
	    	else if(newEntity->getID() == TextEntity::ID){
	    		mc = reinterpret_cast<TextFieldHolder*>(newEntity->getComponent(TextFieldHolder::ID))->getMovieClip();
	    	}
	    	AS3::local::var args[1] = {mc};
	    	FlashHelper::callMethod(movieClipManager, "removeChild", 1, args);
		}
	}
	

	

	void FlashEntityManager::receiveMessage(int senderID, int destID, int message, void *data) {
		if(senderID != State::ID)return;
		if(message == State::MESSAGE_GET_FOCUS){
		   Engine::getInstance().swapActiveMovieClip(movieClipManager);
		}		
		else if(message == State::MESSAGE_ADDED_ENTITY){
		    add(reinterpret_cast<Entity*>(data));
		}
		else if(message == State::MESSAGE_REMOVED_ENTITY){
			remove(reinterpret_cast<Entity*>(data));
		}
		

	}
	
}