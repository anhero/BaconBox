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

		if(destID != Entity::BROADCAST && destID != MovieClipHolder::ID ) return;

		if(senderID == Transform::ID){
			
			inline_as3("var aVar;\n"::);
			AS3_CopyVarxxToVar(aVar, mc);
			inline_as3("var aMovieClip:flash.display.MovieClip;\n"::);
			Vector2 * pos;
			switch(message){
				case Transform::MESSAGE_POSITION_CHANGED:
					pos = (reinterpret_cast<Vector2 *>(data));
					inline_as3("aMovieClip.x = %0;\n aMovieClip.y = %1":: "r"(pos->x), "r"(pos->y));
					break;
				case Transform::MESSAGE_ROTATION_CHANGED:
					return;
					break;
				case Transform::MESSAGE_SCALE_CHANGED:
					return;
					break;
			}	
		}

	}
    
}