/**
 * @file
 */
#ifndef BB_TEXTENTITY_H
#define BB_TEXTENTITY_H

#include "BaconBox/Core/Entity.h"
#include "BaconBox/PlatformFlagger.h"

#include "BaconBox/Components/Transform.h"
#include "BaconBox/Components/TextComponent.h"



namespace BaconBox {
    class Font;
    
    /**
	 * 
	 */
	class TextEntity : public Entity, public TransformProxy, public TextComponentProxy { 
    public:
	BB_ID_HEADER;
	
	TextEntity(Font * font);
	

		
    private:

	};
}

#endif // BB_TEXTENTITY_H
