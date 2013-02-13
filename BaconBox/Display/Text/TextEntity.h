/**
 * @file
 */
#ifndef BB_TEXTENTITY_H
#define BB_TEXTENTITY_H

#include "BaconBox/Core/Entity.h"
#include "BaconBox/PlatformFlagger.h"

#include "BaconBox/Components/Transform.h"
#include "BaconBox/Components/TextRenderer.h"
#include "TextureFont.h"



namespace BaconBox {
	/**
	 * 
	 */
	class TextEntity : public Entity, public TransformProxy, public TextRendererProxy  { 
    public:
	BB_ID_HEADER;
	
	TextEntity(TextureFont * font);
	

		
    private:

	};
}

#endif // BB_TEXTENTITY_H
