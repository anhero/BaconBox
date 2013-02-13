#include "TextRenderer.h"

#include "BaconBox/Core/Entity.h"
#include "BaconBox/Console.h"
#include "Helper/StringHelper.h"
#include "Helper/UTFConvert.h"
#include "Display/Text/TextureFont.h"
#include "EntityFactory.h"

namespace BaconBox {
	 BB_ID_IMPL(TextRenderer);
	
	TextRenderer::TextRenderer() : Component() {
	}

	TextRenderer::~TextRenderer() {
	}
	
	void TextRenderer::render(){
	    for(std::list<MovieClipEntity*>::iterator i = sprites.begin(); i != sprites.end(); i++){
		(*i)->render();
	    }
	}


	void TextRenderer::receiveMessage(int senderID, int destID, int message, void *data) {
		
	}
	
	void TextRenderer::setText(std::string text){
	    String32 text32 = UTFConvert::decodeUTF8(text);
	    for(String32::iterator i = text32.begin(); i != text32.end(); i++ ){
		sprites.push_back(EntityFactory::getMovieClipEntityFromSubTexture(font->getGlyphInformation(*i)->subTextureInfo));
	    }
	}

	
	TextRendererProxy::TextRendererProxy(Entity* entity, TextureFont * font, bool mustAddComponent): BB_PROXY_CONSTRUCTOR(new TextRenderer())  {
	    reinterpret_cast<TextRenderer*>(component)->font = font;
	}
	    
	    
	void TextRendererProxy::setText(std::string text){
	    reinterpret_cast<TextRenderer*>(component)->setText(text);
	}
	
}