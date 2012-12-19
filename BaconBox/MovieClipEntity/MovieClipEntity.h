/**
 * @file
 */
#ifndef BB_MOVIECLIPENTITY_H
#define BB_MOVIECLIPENTITY_H

#include "../Core/Entity.h"

#ifdef BB_FLASH_PLATEFORM
#include "Flash/MovieClipHolder.h"
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
#endif
		int getNumber();

	
    private:
		int test;
	};
}

#endif // BB_MOVIECLIPENTITY_H