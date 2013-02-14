#include "TextRenderer.h"

#include "BaconBox/Core/Entity.h"
#include "BaconBox/Console.h"
#include "Helper/StringHelper.h"
#include "Helper/UTFConvert.h"
#include "Display/Text/TextureFont.h"
#include "EntityFactory.h"
#include "Mesh.h"
#include "BaconBox/Display/Text/TextureFont.h"
namespace BaconBox {
    
	struct CharSprite{
	    CharSprite(MovieClipEntity * sprite, TextureGlyphInformation * glyph): sprite(sprite), glyph(glyph), currentPos(){}
		MovieClipEntity * sprite;
		TextureGlyphInformation * glyph;    
		Vector2 currentPos;
	};
	
	BB_ID_IMPL(TextRenderer);
	
	TextRenderer::TextRenderer(TextureFont * font) : Component(), font(font) {
	}

	TextRenderer::~TextRenderer() {
	}
	
	void TextRenderer::render(){
	    for(std::list<CharSprite>::iterator i = charSprites.begin(); i != charSprites.end(); i++){
		i->sprite->render();
	    }
	}


	void TextRenderer::receiveMessage(int senderID, int destID, int message, void *data) {
	    if(senderID == Transform::ID){
		if(message == Transform::MESSAGE_POSITION_CHANGED || message == Transform::MESSAGE_ROTATION_CHANGED || message == Transform::MESSAGE_SCALE_CHANGED){
		    resetPosition();
		}
	    }
	    else if(senderID == TextComponent::ID){
			if(message == TextComponent::MESSAGE_TEXT_CHANGED ){
			setText(*reinterpret_cast<std::string*>(data));
			}
		}
	}
	
	void TextRenderer::resetPosition(){
	    Vector2 advance;
	    Char32 previousChar;
	    Transform* stringTransform = reinterpret_cast<Transform*>(getEntity()->getComponent(Transform::ID));
	    for(std::list<CharSprite>::iterator i = charSprites.begin(); i != charSprites.end(); i++){
		TextureGlyphInformation * glyphInfo = i->glyph;
		MovieClipEntity * sprite = i->sprite;
		Transform* transform = reinterpret_cast<Transform*>(sprite->getComponent(Transform::ID));
		Mesh* mesh = reinterpret_cast<Mesh*>(sprite->getComponent(Mesh::ID));
		(*transform) = (*stringTransform);
		Vector2 glypRelativePosition = transform->getPosition() +advance+ glyphInfo->offset + Vector2(font->getKerning(previousChar, i->glyph->charCode),0);
		Vector2 neededMove = glypRelativePosition - i->currentPos;
		mesh->getVertices().move(neededMove.x, neededMove.y);
		i->currentPos = glypRelativePosition;
		advance += glyphInfo->advance;
		previousChar = glyphInfo->charCode;

	    }
	}
	
	void TextRenderer::setText(const std::string & text){
	    for(std::list<CharSprite>::iterator i = charSprites.begin(); i != charSprites.end(); i++ ){
		if(i->sprite) delete i->sprite;
	    }
	    
	    charSprites.clear();
	    
	    String32 text32 = UTFConvert::decodeUTF8(text);
	    for(String32::iterator i = text32.begin(); i != text32.end(); i++ ){
		TextureGlyphInformation * glyphInfo = font->getGlyphInformation(*i);
		if(glyphInfo == NULL){
		     glyphInfo = font->getGlyphInformation(-1);
			if(glyphInfo == NULL){
				glyphInfo = font->getGlyphInformation(32);
			}
		}
		MovieClipEntity * sprite = EntityFactory::getMovieClipEntityFromSubTexture(glyphInfo->subTextureInfo);
		charSprites.push_back(CharSprite(sprite, glyphInfo));
	    }
	    
	    resetPosition();
	}

	
}