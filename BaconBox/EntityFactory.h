#ifndef BB_ENTITY_FACTORY_H
#define BB_ENTITY_FACTORY_H

#include "BaconBox/Core/Entity.h"
#include "BaconBox/MovieClipEntity/MovieClipEntity.h"
#include "BaconBox/Display/TexturePointer.h"

namespace BaconBox {

	class EntityFactory {
	public:
	   
	    static MovieClipEntity * getMovieClipEntity(const std::string & key);
	#if ! defined(BB_FLASH_PLATEFORM)
		static Entity *getTexturedEntity(TexturePointer texture);
	#endif //! defined(BB_FLASH_PLATEFORM)
	private:
		    
		
	};

}

#endif
