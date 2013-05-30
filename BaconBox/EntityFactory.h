#ifndef BB_ENTITY_FACTORY_H
#define BB_ENTITY_FACTORY_H

#include "BaconBox/Core/Entity.h"
#include "BaconBox/MovieClipEntity/MovieClipEntity.h"
#include "BaconBox/Display/TexturePointer.h"
#include "BaconBox/Display/Text/TextEntity.h"
#include "BaconBox/Helper/DynamicPool.h"

namespace BaconBox {

	class EntityFactory {
	public:
		
	    static void initMovieClipPool(int size);
		
		static MovieClipEntity *getMovieClipEntity(const std::string &key, bool autoPlay = false);
#if defined(BB_FLASH_PLATFORM)
		static TextEntity *getTextEntity(const std::string &key);
#endif
		static EntityFactory &getInstance();

		
		MovieClipEntity *internalGetMovieClipEntity(const std::string &key, bool autoPlay = false);
#if ! defined(BB_FLASH_PLATFORM)
		MovieClipEntity *getMovieClipEntityFromSymbol(Symbol* symbol, bool autoPlay = false);
		MovieClipEntity *getMovieClipEntityFromSubTexture(SubTextureInfo* subTex, const Vector2 & origin = Vector2(), bool blend = true);
#endif

	private:
		
		EntityFactory();
		DynamicPool<MovieClipEntity> movieClipPool;

	};

}

#endif
