/**
 * @file
 */
#ifndef BB_TEXTENTITY_H
#define BB_TEXTENTITY_H

#include "BaconBox/Core/Entity.h"
#include "BaconBox/PlatformFlagger.h"

#include "BaconBox/Components/Transform.h"
#include "BaconBox/Components/TextComponent.h"
#include "BaconBox/Components/ColorFilter.h"

#ifdef BB_FLASH_PLATEFORM
#include <AS3/AS3.h>
#include <AS3/AS3++.h>
#endif
namespace BaconBox {
    class Font;
    
    /**
	 * 
	 */
class TextEntity : public Entity, public TransformProxy, public ColorFilterProxy, public TextComponentProxy { 
    public:
	BB_ID_HEADER;
	TextEntity();
	TextEntity(Font * font);

	#ifdef BB_FLASH_PLATEFORM
		void setMovieClip(AS3::local::var aMC);
	#endif
	

		
    private:

	};
}

#endif // BB_TEXTENTITY_H
