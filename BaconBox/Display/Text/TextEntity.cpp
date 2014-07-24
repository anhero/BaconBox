#include "TextEntity.h"
#include <string>
#include "Font.h"
#if ! defined(BB_FLASH_PLATFORM)
#include "BaconBox/Display/Text/StandardRenderer/TextureFont.h"
#include "BaconBox/Components/StandardRenderer/TextRenderer.h"
#include "BaconBox/Components/DefaultEntityContainer.h"

#else
#include "BaconBox/Components/Flash/TextFieldHolder.h"

#endif
#include "BaconBox/LocalizationManager.h"
namespace BaconBox {
    
    BB_ID_IMPL(TextEntity);
	TextEntity::TextEntity(Font * font): MovieClipEntity(), TextComponentProxy(this, font)
	{
	    
#if ! defined(BB_FLASH_PLATFORM)
	    if(font->getFormat() == FontFormat::BMFONT){
		addComponent(new TextRenderer(reinterpret_cast<TextureFont*>(font)));
	    }
#else

#endif
	    
	    
	}
	
	TextEntity::~TextEntity(){
		LocalizationManager::getInstance().removeTextEntity(this);
	}
	
	TextEntity::TextEntity(): MovieClipEntity(), TextComponentProxy(this, NULL)
	{
	#if ! defined(BB_FLASH_PLATFORM)
	#else

	#endif	
	}

	#ifdef BB_FLASH_PLATFORM
	void TextEntity::setMovieClip(AS3::local::var aMC) {
		TextFieldHolder *tfHolder = new TextFieldHolder(aMC);
		addComponent(tfHolder);   
		
	}
	#endif


}
