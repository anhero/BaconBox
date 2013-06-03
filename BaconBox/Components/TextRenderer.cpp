#include "TextRenderer.h"

#include "BaconBox/Core/Entity.h"
#include "BaconBox/Console.h"
#include "BaconBox/Helper/StringHelper.h"
#include "BaconBox/Helper/UTFConvert.h"
#include "BaconBox/Display/Text/TextureFont.h"
#include "BaconBox/EntityFactory.h"
#include "Mesh.h"
#include "BaconBox/Display/Text/TextureFont.h"
#include "BaconBox/Components/ComponentConnection.h"
#include "DefaultEntityContainer.h"

namespace BaconBox {

	struct CharSprite{
	    CharSprite(MovieClipEntity * sprite, TextureGlyphInformation * glyph): sprite(sprite), glyph(glyph), currentPos(){}
		MovieClipEntity * sprite;
		TextureGlyphInformation * glyph;
		Vector2 currentPos;
	};

	BB_ID_IMPL(TextRenderer);

	TextRenderer::TextRenderer(TextureFont * font) : Component(), font(font), needPositionReset(false), alignment(TextAlignment::LEFT), textComponent(NULL) {
		this->initializeConnections();
	}

	TextRenderer::~TextRenderer() {
	}

	void TextRenderer::initializeConnections() {
		// We add the connections.
		this->addConnection(new ComponentConnection<TextComponent>(&this->textComponent));
		this->refreshConnections();
	}


	void TextRenderer::update(){
		if(needPositionReset){
			internalResetPosition();
			needPositionReset =false;
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

	void TextRenderer::setEntity(Entity *newEntity){
	    Component::setEntity(newEntity);
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
		else if(senderID == ColorTransform::ID && message == ColorTransform::MESSAGE_COLOR_CHANGED){
            setColor(*reinterpret_cast<Color*>(data));
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
				mesh->getPreTransformVertices().move(alignmentAdjust.x, alignmentAdjust.y);
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


	void TextRenderer::internalResetPosition(){
	    Vector2 advance;
	    Vector2 tempAdvance;
	    Vector2 newLineJump;
	    Char32 previousChar;
	    std::list<CharSprite> charSpritesForAlignmentAdjust;

//	    Transform* stringTransform = reinterpret_cast<Transform*>(getEntity()->getComponent(Transform::ID));
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
//					Transform* transform = reinterpret_cast<Transform*>(sprite->getComponent(Transform::ID));
					Mesh* mesh = reinterpret_cast<Mesh*>(sprite->getComponent(Mesh::ID));
					Vector2 glypRelativePosition = advance+ glyphInfo->offset + Vector2(font->getKerning(previousChar, k->glyph->charCode),0) + newLineJump;
//					Vector2 glypRelativePosition = transform+ advance+ glyphInfo->offset + Vector2(font->getKerning(previousChar, k->glyph->charCode),0) + newLineJump;

					Vector2 neededMove = glypRelativePosition - k->currentPos;
					if(neededMove.x || neededMove.y){
					    mesh->getPreTransformVertices().move(neededMove.x, neededMove.y);
					}
//					(*transform) = (*stringTransform);
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
		setColor(reinterpret_cast<TextEntity*>(getEntity())->getColor());
	}

	void TextRenderer::setText(const std::string & text){
	    getEntity()->getComponent<DefaultEntityContainer>()->removeAllChildren();
	    for(std::list<std::list<std::list<CharSprite> > >::iterator i = charSpritesLines.begin(); i != charSpritesLines.end(); i++ ){
		for(std::list<std::list<CharSprite> >::iterator j = i->begin(); j != i->end(); j++){
		    for(std::list<CharSprite>::iterator k = j->begin(); k != j->end(); k++){
			if(k->sprite) delete k->sprite;
		    }
		}
	    }

	    getEntity()->getComponent<DefaultTimeline>()->setNbFrames(1);


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
		MovieClipEntity * sprite = NULL;
		if(glyphInfo->charCode == '\n'){
			charSpritesLines.resize(charSpritesLines.size() +1 );
			charSpritesLines.back().resize(1);
		}
		else if(glyphInfo->charCode == ' '){
			line.resize(line.size() +1);
			sprite = EntityFactory::getInstance().getMovieClipEntityFromSubTexture(glyphInfo->subTextureInfo);
			line.back().push_back(CharSprite(sprite, glyphInfo));
			line.resize(line.size() +1);
		}
		else{
		    sprite = EntityFactory::getInstance().getMovieClipEntityFromSubTexture(glyphInfo->subTextureInfo);
		    word.push_back(CharSprite(sprite, glyphInfo));
		}
		if(sprite)getEntity()->getComponent<DefaultEntityContainer>()->addChild(sprite);


	    }
	    	    getEntity()->getComponent<DefaultTimeline>()->gotoAndStop(0);


	    resetPosition();

	}


}
