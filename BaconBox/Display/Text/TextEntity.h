/**
 * @file
 */
#ifndef BB_TEXTENTITY_H
#define BB_TEXTENTITY_H

#include "BaconBox/Core/Entity.h"
#include "BaconBox/PlatformFlagger.h"

#include "BaconBox/Components/Transform.h"
#include "BaconBox/Components/TextComponent.h"
#include "BaconBox/Components/EntityContainer.h"
#include "BaconBox/MovieClipEntity/MovieClipEntity.h"
#ifdef BB_FLASH_PLATFORM
#include <AS3/AS3.h>
#include <AS3/AS3++.h>
#endif
namespace BaconBox {
    class Font;
    
    /**
	 * 
	 */
class TextEntity : public MovieClipEntity, public TextComponentProxy { 
    public:
	BB_ID_HEADER;
	TextEntity();
	TextEntity(Font * font);
	~TextEntity();
	#ifdef BB_FLASH_PLATFORM
		void setMovieClip(AS3::local::var aMC);
	#endif
	

		
    private:

	};
}

#endif // BB_TEXTENTITY_H
