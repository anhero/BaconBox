#include "MovieClipHolder.h"
#include "BaconBox/Core/Entity.h"
#include "BaconBox/Components/Transform.h"
#include "BaconBox/Core/IDManager.h"





namespace BaconBox {
	
	int MovieClipHolder::ID = IDManager::getID();

	MovieClipHolder::MovieClipHolder(AS3::local::var aMC) : Component(){


		setName("MovieClipHolder");
		setMovieClip(aMC);
	}
	
	void MovieClipHolder::setMovieClip(AS3::local::var aMC){
		mc = aMC;
	}
	
	AS3::local::var MovieClipHolder::getMovieCLip(){
		return mc;
	}


	void MovieClipHolder::setProperty(const std::string & propertyName, AS3::local::var arg){
		AS3::local::var propertyNameAS = AS3::local::internal::new_String(propertyName.c_str());
		AS3::local::internal::setproperty(mc, propertyNameAS, arg);
	}

	AS3::local::var MovieClipHolder::getProperty(const std::string & propertyName){
		AS3::local::var propertyNameAS = AS3::local::internal::new_String(propertyName.c_str());
		return  AS3::local::internal::getproperty(mc, propertyNameAS);
	}

	AS3::local::var MovieClipHolder::callFunction(const std::string & functionName, int argCount, AS3::local::var *args){
		AS3::local::var functionNameAS = AS3::local::internal::new_String(functionName.c_str());
		AS3::local::var functionAS = AS3::local::internal::getproperty(mc, functionNameAS);
		return AS3::local::internal::call(functionAS, AS3::local::internal::_null, argCount, args);
	} 

	void MovieClipHolder::receiveMessage(int senderID, int destID, int message, void *data){
		 if(destID != Entity::BROADCAST && destID != MovieClipHolder::ID ) return;

		 if(senderID == Transform::ID){
		 	if(message == Transform::MESSAGE_POSITION_CHANGED)	{
				Vector2 * pos = (reinterpret_cast<Vector2 *>(data));
				setProperty("x", AS3::local::internal::new_int(pos->x));
				setProperty("y", AS3::local::internal::new_int(pos->y));
		 	}	
		 	else if(message == Transform::MESSAGE_ROTATION_CHANGED){

		 	}
		 	else if(message == Transform::MESSAGE_SCALE_CHANGED){

		 	}	
		 }

	}
    
}