/**
 * @file
 */
#ifndef BB_MOVIECLIPENTITY_H
#define BB_MOVIECLIPENTITY_H

#include "BaconBox/Core/Entity.h"

#include "BaconBox/PlatformFlagger.h"

#ifdef BB_FLASH_PLATEFORM
#include "Flash/MovieClipHolder.h"
#else
#include "BaconBox/Components/Mesh.h"
#endif
namespace BaconBox {
	/**
	 * 
	 */
	class MovieClipEntity : public Entity { 
    public:
#ifdef BB_FLASH_PLATEFORM
		MovieClipEntity(AS3::local::var aMC);
		void setMovieClip(AS3::local::var aMC);
#else
		MovieClipEntity();
#endif
		

	
    private:
#ifndef BB_FLASH_PLATEFORM
		Mesh * mesh;
#endif
		
		
	};
}

#endif // BB_MOVIECLIPENTITY_H
