#include "EntityFactory.h"

#include "BaconBox/PlatformFlagger.h"
#ifdef BB_FLASH_PLATEFORM	
	#include <AS3/AS3.h>
	#include <AS3/AS3++.h>
	#include "BaconBox/Helper/Flash/FlashHelper.h"

#endif	



namespace BaconBox {
	
	MovieClipEntity * EntityFactory::getMovieClipEntity(const std::string & key){
		#ifdef BB_FLASH_PLATEFORM	
			AS3::local::var mc =  FlashHelper::construct(key);
			AS3::local::var entity = FlashHelper::getProperty(mc, "entity");
			AS3::local::var entityPointerAS3 = FlashHelper::getProperty(entity, "swigCPtr");
			MovieClipEntity * entityPointer = (MovieClipEntity*)int_valueOf(entityPointerAS3);
			return entityPointer;
		#endif	  
	}
}

