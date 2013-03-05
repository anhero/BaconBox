#include "TextRenderer.h"

#include "BaconBox/Core/Entity.h"
#include "BaconBox/Console.h"
#include "BaconBox/Helper/StringHelper.h"
#include "BaconBox/Helper/UTFConvert.h"
#include "BaconBox/Display/Text/TextureFont.h"
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
	
	TextRenderer::TextRenderer(TextureFont * font) : Component(), font(font), needPositionReset(false), alignment(TextAlignment::LEFT) {
	   
	}

	TextRenderer::~TextRenderer() {
	}
	
	void TextRenderer::render(){
		if(needPositionReset){
			internalResetPosition();
			needPositionReset =false;
		}
	    for(std::list<std::list<std::list<CharSprite> > >::iterator i = charSpritesLines.begin(); i != charSpritesLines.end(); i++){
		      for(std::list<std::list<CharSprite> >::iterator j = i->begin(); j != i->end(); j++){
			  for(std::list<CharSprite>::iterator k = j->begin(); k != j->end(); k++){
			      k->sprite->render();
			  }	
		    }
		}
		}

	void TextRenderer::setColor(const Color &newColor){
	    color = newColor;
	    for(std::list<std::list<std::list<CharSprite> > >::iterator i = charSpritesLines.begin(); i != charSpritesLines.end(); i++){
		      for(std::list<std::list<CharSprite> >::iterator j = i->begin(); j != i->end(); j++){
			  for(std::list<CharSprite>::iterator k = j->begin(); k != j->end(); k++){
			      k->sprite->setColor(color);
			  }	
		    }
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
			else if(message == TextComponent::MESSAGE_ALIGNMENT_CHANGED ){
			    alignment = *reinterpret_cast<TextAlignment::type*>(data);
			    resetPosition();
			}
			else if(message == TextComponent::MESSAGE_SIZE_CHANGED){
			    resetPosition();
			}
		}
		else if(destID == TextRenderer::ID && message == Entity::MESSAGE_ADDING_COMPONENT){
		    textComponent = reinterpret_cast<TextComponent*>(getEntity()->getComponent(TextComponent::ID));
		}
		else if(senderID == ColorFilter::ID){
			if(message == ColorFilter::MESSAGE_COLOR_CHANGED ){
				setColor(*reinterpret_cast<Color*>(data));
			}
		}
	}
	
	bool TextRenderer::isWordJump(Char32 charCode){
		std::string wordJump = "\n\t ";
		return wordJump.find(charCode) != std::string::npos;
	}

	void TextRenderer::lineJump(Vector2 & newLineJump, Vector2 & advance,  std::list<CharSprite> &charSpritesForAlignmentAdjust){
		while (charSpritesForAlignmentAdjust.size() != 0 && charSpritesForAlignmentAdjust.back().glyph->charCode == ' ') {
			advance -= charSpritesForAlignmentAdjust.back().glyph->advance;
			charSpritesForAlignmentAdjust.pop_back();
		}
		Vector2 alignmentAdjust;
		
		if(alignment == TextAlignment::RIGHT){
			alignmentAdjust.x = (textComponent->getSize().x - (advance.x));
			
		}
		else if(alignment == TextAlignment::CENTER){
			alignmentAdjust.x = (textComponent->getSize().x - (advance.x))/2;
		}
		if(true || alignment != TextAlignment::LEFT){
			for(std::list<CharSprite>::iterator k = charSpritesForAlignmentAdjust.begin(); k != charSpritesForAlignmentAdjust.end(); k++){
				MovieClipEntity * sprite = k->sprite;
				Mesh* mesh = reinterpret_cast<Mesh*>(sprite->getComponent(Mesh::ID));
				Transform* transform = reinterpret_cast<Transform*>(sprite->getComponent(Transform::ID));
				Transform transformBackup = *transform;
				(*transform) = Transform();
				mesh->getVertices().move(alignmentAdjust.x, alignmentAdjust.y);
				(*transform) = transformBackup;
			}
		}
	    	charSpritesForAlignmentAdjust.clear();
		newLineJump.y += font->getLineHeight();
		advance = Vector2();
	}
	
	void TextRenderer::resetPosition(){
		needPositionReset = true;
	}
	
	void TextRenderer::update(){
		if(needPositionReset){
			internalResetPosition();
			needPositionReset =false;
		}
	}

	
	void TextRenderer::internalResetPosition(){
	    Vector2 advance;
	    Vector2 tempAdvance;
	    Vector2 newLineJump;
	    Char32 previousChar;
	    int widthLastChar = 0;
	    std::list<CharSprite> charSpritesForAlignmentAdjust;
	    
	    Transform* stringTransform = reinterpret_cast<Transform*>(getEntity()->getComponent(Transform::ID));
	    for(std::list<std::list<std::list<CharSprite> > >::iterator i = charSpritesLines.begin(); i != charSpritesLines.end(); i++){
			for(std::list<std::list<CharSprite> >::iterator j = i->begin(); j != i->end(); j++){
				Vector2 wordTempAdvances;
				for(std::list<CharSprite>::iterator k = j->begin(); k != j->end(); k++){
					TextureGlyphInformation * glyphInfo = k->glyph;
					wordTempAdvances += glyphInfo->advance;
				}
				tempAdvance += wordTempAdvances;
				
				if(tempAdvance.x > textComponent->getSize().x){
					tempAdvance = wordTempAdvances;
					lineJump(newLineJump, advance, charSpritesForAlignmentAdjust);
				}
				
				for(std::list<CharSprite>::iterator k = j->begin(); k != j->end(); k++){
					TextureGlyphInformation * glyphInfo = k->glyph;
					MovieClipEntity * sprite = k->sprite;
					Transform* transform = reinterpret_cast<Transform*>(sprite->getComponent(Transform::ID));
					Mesh* mesh = reinterpret_cast<Mesh*>(sprite->getComponent(Mesh::ID));
					Vector2 glypRelativePosition = transform->getPosition() +advance+ glyphInfo->offset + Vector2(font->getKerning(previousChar, k->glyph->charCode),0) + newLineJump;
					Vector2 neededMove = glypRelativePosition - k->currentPos;
					if(neededMove.x || neededMove.y)mesh->getVertices().move(neededMove.x, neededMove.y);
					(*transform) = (*stringTransform);
					k->currentPos = glypRelativePosition;
					advance += glyphInfo->advance;
					previousChar = glyphInfo->charCode;
					charSpritesForAlignmentAdjust.push_back(*k);
				}
				
			}
			tempAdvance = Vector2();
			
			lineJump(newLineJump, advance, charSpritesForAlignmentAdjust);
	    }
		lineJump(newLineJump, advance, charSpritesForAlignmentAdjust);
	}
	
	void TextRenderer::setText(const std::string & text){
	    for(std::list<std::list<std::list<CharSprite> > >::iterator i = charSpritesLines.begin(); i != charSpritesLines.end(); i++ ){
		for(std::list<std::list<CharSprite> >::iterator j = i->begin(); j != i->end(); j++){
		    for(std::list<CharSprite>::iterator k = j->begin(); k != j->end(); k++){
			if(k->sprite) delete k->sprite;
		    }
		}
	    }
	    
	    charSpritesLines.clear();
	    
	    String32 text32 = UTFConvert::decodeUTF8(text);
	    charSpritesLines.resize(1);
	    
	    charSpritesLines.back().resize(1);
	    
	    for(String32::iterator i = text32.begin(); i != text32.end(); i++ ){
		std::list<std::list<CharSprite> >  & line = charSpritesLines.back();
			std::list<CharSprite> & word = line.back();
		TextureGlyphInformation * glyphInfo = font->getGlyphInformation(*i);
		if(glyphInfo == NULL){
		     glyphInfo = font->getGlyphInformation(-1);
			if(glyphInfo == NULL){
				glyphInfo = font->getGlyphInformation(32);
			}
		}
		
		if(glyphInfo->charCode == '\n'){
			charSpritesLines.resize(charSpritesLines.size() +1 );
			charSpritesLines.back().resize(1);
		}
		else if(glyphInfo->charCode == ' '){
			line.resize(line.size() +1);
			MovieClipEntity * sprite = EntityFactory::getMovieClipEntityFromSubTexture(glyphInfo->subTextureInfo);
			line.back().push_back(CharSprite(sprite, glyphInfo));
			line.resize(line.size() +1);
		}
		else{
		    MovieClipEntity * sprite = EntityFactory::getMovieClipEntityFromSubTexture(glyphInfo->subTextureInfo);
		    word.push_back(CharSprite(sprite, glyphInfo));
		}

		
	    }
	    
	    resetPosition();
	    setColor(color);
	    
	}

	
}