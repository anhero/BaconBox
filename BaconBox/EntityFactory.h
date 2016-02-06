#ifndef BB_ENTITY_FACTORY_H
#define BB_ENTITY_FACTORY_H

#include "BaconBox/Core/Entity.h"
#include "BaconBox/MovieClipEntity/MovieClipEntity.h"
#include "BaconBox/Display/Text/TextEntity.h"
#include "BaconBox/Helper/DynamicPool.h"

namespace BaconBox {

	class EntityFactory {
	public:
		
	    static void initMovieClipPool(int size);
		static MovieClipEntity *getMovieClipEntity();
		static MovieClipEntity *getMovieClipEntity(const std::string &key, bool autoPlay = false);
        static void claimMovieClipEntity(MovieClipEntity * mc);
        
#if defined(BB_FLASH_PLATFORM)
		static TextEntity *getTextEntity(const std::string &key);
#endif
		static EntityFactory &getInstance();
        
        void internalClaimMovieClipEntity(MovieClipEntity * mc);
		MovieClipEntity *internalGetMovieClipEntity();
		MovieClipEntity *internalGetMovieClipEntity(const std::string &key, bool autoPlay = false);
#if ! defined(BB_FLASH_PLATFORM)
		MovieClipEntity *getMovieClipEntityFromSymbol(Symbol* symbol, bool autoPlay = false);
		MovieClipEntity *getMovieClipEntityFromSubTexture(SubTextureInfo* subTex, const Vector2 & origin = Vector2(), bool blend = true, float scale = 1.0f);
#endif

		/// Creates a MovieClip with no Texture component, with width `w` and height `h`.
		static MovieClipEntity *getShapeRectangle(float w, float h, const Vector2 & origin = Vector2(), bool blend = true, float scale = 1.0f);
		MovieClipEntity *internalGetShapeRectangle(float w, float h, const Vector2 & origin = Vector2(), bool blend = true, float scale = 1.0f);

		static MovieClipEntity *getRegularPolygon(unsigned int nbSides, float sideLength, bool blend = true, float scale = 1.0f);
		MovieClipEntity *internalGetRegularPolygon(unsigned int nbSides, float sideLength, bool blend = true, float scale = 1.0f);

	private:
		
		EntityFactory();
		DynamicPool<MovieClipEntity> movieClipPool;

	};

}

#endif
