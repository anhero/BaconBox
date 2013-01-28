#include "MovieClipHolder.h"
#include "BaconBox/Core/Entity.h"
#include "BaconBox/Components/Transform.h"
#include "BaconBox/Core/IDManager.h"


#include "BaconBox/Helper/Flash/FlashHelper.h"


namespace BaconBox {
	
	int MovieClipHolder::ID = IDManager::getID();

	MovieClipHolder::MovieClipHolder(AS3::local::var aMC) : Component(){


		setName("MovieClipHolder");
		setMovieClip(aMC);
		AS3::local::var args[1] = {AS3::local::internal::new_int(1)};
		callMethod("gotoAndStop", 1, args);
	}
	
	void MovieClipHolder::setMovieClip(AS3::local::var aMC){
		mc = aMC;
	}
	
	AS3::local::var MovieClipHolder::getMovieCLip(){
		return mc;
	}


	void MovieClipHolder::setProperty(const std::string & propertyName, AS3::local::var arg){
		FlashHelper::setProperty(mc, propertyName, arg);
	}

	AS3::local::var MovieClipHolder::getProperty(const std::string & propertyName){
		return FlashHelper::getProperty(mc, propertyName);
	}

	AS3::local::var MovieClipHolder::callMethod(const std::string & functionName, int argCount, AS3::local::var *args){
		return FlashHelper::callMethod(mc, functionName, argCount, args);
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
		 		float rotation = *reinterpret_cast<float*>(data);
		 		setProperty("rotation", AS3::local::internal::new_Number(rotation));

		 	}
		 	else if(message == Transform::MESSAGE_SCALE_CHANGED){
		 		Vector2 * scale = (reinterpret_cast<Vector2 *>(data));
		 		setProperty("scaleX", AS3::local::internal::new_Number(scale->x));
				setProperty("scaleY", AS3::local::internal::new_Number(scale->y));
		 	}	
		 }

	}
    
}