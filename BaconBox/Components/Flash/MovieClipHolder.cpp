#include "MovieClipHolder.h"
#include "BaconBox/Core/Entity.h"
#include "BaconBox/Components/Transform.h"
#include "BaconBox/Core/IDManager.h"


#include "BaconBox/Helper/Flash/FlashHelper.h"
#include "BaconBox/Console.h"
#include "BaconBox/Helper/Vector2ChangedData.h"

namespace BaconBox {

	BB_ID_IMPL(MovieClipHolder);
	

	MovieClipHolder::MovieClipHolder(AS3::local::var aMC) : Component(){
		setMovieClip(aMC);
		AS3::local::var args[1] = {AS3::local::internal::new_int(1)};
		callMethod("gotoAndStop", 1, args);
	}

	void MovieClipHolder::setMovieClip(AS3::local::var aMC){
		mc = aMC;
	}
	
	AS3::local::var MovieClipHolder::getMovieClip(){
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
				Vector2ChangedData * pos = (reinterpret_cast<Vector2ChangedData *>(data));
				setProperty("x", AS3::local::internal::new_int(pos->newValue.x));
				setProperty("y", AS3::local::internal::new_int(pos->newValue.y));
		 	}	
		 	else if(message == Transform::MESSAGE_ROTATION_CHANGED){
		 		ValueChangedData<float>* rotation= reinterpret_cast<ValueChangedData<float>*>(data);
		 		setProperty("rotation", AS3::local::internal::new_Number(rotation->newValue));

		 	}
		 	else if(message == Transform::MESSAGE_SCALE_CHANGED){
		 		Vector2ChangedData * scale = (reinterpret_cast<Vector2ChangedData *>(data));
		 		setProperty("scaleX", AS3::local::internal::new_Number(scale->newValue.x));
				setProperty("scaleY", AS3::local::internal::new_Number(scale->newValue.y));
		 	}	
		 }

	}
    
}