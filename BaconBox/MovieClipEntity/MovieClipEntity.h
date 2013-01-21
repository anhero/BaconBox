/**
 * @file
 */
#ifndef BB_MOVIECLIPENTITY_H
#define BB_MOVIECLIPENTITY_H

#include "BaconBox/Core/Entity.h"

#include "BaconBox/PlatformFlagger.h"

#ifdef BB_FLASH_PLATEFORM
#include "BaconBox/ComponentS/Flash/MovieClipHolder.h"
#else
#include "BaconBox/Components/Mesh.h"
#endif
namespace BaconBox {
	/**
	 * 
	 */
	class MovieClipEntity : public Entity { 
    public:
	MovieClipEntity();
	
#ifdef BB_FLASH_PLATEFORM
		void setMovieClip(AS3::local::var aMC);
#endif
		
    private:
#if !defined(BB_FLASH_PLATEFORM)
		Mesh * mesh;
#endif
		
	};
}

#endif // BB_MOVIECLIPENTITY_H
