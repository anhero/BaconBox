#include "TextEntity.h"
#include <string>



namespace BaconBox {
    
    BB_ID_IMPL(TextEntity);
    
	TextEntity::TextEntity(TextureFont * font): Entity(), TransformProxy(this), TextRendererProxy(this, font){


	}



}
