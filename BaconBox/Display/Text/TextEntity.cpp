#include "TextEntity.h"
#include <string>
#include "Font.h"
#if ! defined(BB_FLASH_PLATEFORM)
#include "TextureFont.h"
#include "Components/TextRenderer.h"
#endif

namespace BaconBox {
    
    BB_ID_IMPL(TextEntity);
    
	TextEntity::TextEntity(Font * font): Entity(), TransformProxy(this), TextComponentProxy(this, font)
	{
	    if(font->getFormat() == FontFormat::BMFONT){
		addComponent(new TextRenderer(reinterpret_cast<TextureFont*>(font)));
	    }


	}



}
