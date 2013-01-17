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


	void MovieClipHolder::receiveMessage(int senderID, int destID, int message, void *data){
		AS3::local::var propertyName = AS3::local::internal::new_String("x");
		AS3::local::var newValue = AS3::local::internal::new_int(100);
		AS3::local::internal::setproperty(mc, propertyName, newValue);

		AS3::local::var functionName = AS3::local::internal::new_String("gotoAndStop");
		AS3::local::var gotoAndStopFunction = AS3::local::internal::getproperty(mc, functionName);
		newValue = AS3::local::internal::new_int(2);
		AS3::local::var args[1] ={newValue};
		AS3::local::internal::call(gotoAndStopFunction, AS3::local::internal::_null, 1, args);
		//bob->x = 100;
		// if(destID != Entity::BROADCAST && destID != MovieClipHolder::ID ) return;

		// if(senderID == Transform::ID){
			
		// 	inline_as3("var aVar;\n"::);
		// 	AS3_CopyVarxxToVar(aVar, mc);
		// 	inline_as3("var aMovieClip:flash.display.MovieClip;\n"::);
		// 	Vector2 * pos;
		// 	switch(message){
		// 		case Transform::MESSAGE_POSITION_CHANGED:
		// 			pos = (reinterpret_cast<Vector2 *>(data));
		// 			inline_as3("aMovieClip.x = %0;\n aMovieClip.y = %1":: "r"(pos->x), "r"(pos->y));
		// 			break;
		// 		case Transform::MESSAGE_ROTATION_CHANGED:
		// 			return;
		// 			break;
		// 		case Transform::MESSAGE_SCALE_CHANGED:
		// 			return;
		// 			break;
		// 	}	
		// }

	}
    
}