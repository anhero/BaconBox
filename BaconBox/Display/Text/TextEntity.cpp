#include "TextEntity.h"
#include <string>
#include "Font.h"
#if ! defined(BB_FLASH_PLATEFORM)
#include "TextureFont.h"
#include "BaconBox/Components/TextRenderer.h"
#else
#include "BaconBox/Components/Flash/TextFieldHolder.h"

#endif

namespace BaconBox {
    
    BB_ID_IMPL(TextEntity);
	TextEntity::TextEntity(Font * font): Entity(), TransformProxy(this), TextComponentProxy(this, font)
	{
	    
#if ! defined(BB_FLASH_PLATEFORM)
	    if(font->getFormat() == FontFormat::BMFONT){
		addComponent(new TextRenderer(reinterpret_cast<TextureFont*>(font)));
	    }
#endif
	}
	
	TextEntity::TextEntity(): Entity(), TransformProxy(this), TextComponentProxy(this, NULL)
	{
		
	}

	#ifdef BB_FLASH_PLATEFORM
	void TextEntity::setMovieClip(AS3::local::var aMC) {
		TextFieldHolder *tfHolder = new TextFieldHolder(aMC);
		addComponent(tfHolder);    
//		setFont(new FlashFont());
		
	}
	#endif


}
