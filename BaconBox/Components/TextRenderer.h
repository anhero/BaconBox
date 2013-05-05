#ifndef BB_TEXTRENDERER_H
#define BB_TEXTRENDERER_H

#include "BaconBox/Core/Component.h"
#include "BaconBox/Vector2.h"
#include "BaconBox/Core/Entity.h"

#include "BaconBox/MovieClipEntity/MovieClipEntity.h"
#include "BaconBox/Display/Text/TextAlignment.h"
#include "TextComponent.h"
#include "BaconBox/Helper/String32.h"
namespace BaconBox {
    class TextureFont;
    struct CharSprite;

	class TextRenderer : public Component {
	public:
		BB_ID_HEADER;

	
	
		TextRenderer(TextureFont * font);
		
		virtual void render();
		void update();
	
		virtual ~TextRenderer();
		void initializeConnections();
		void setText(const std::string & text);
		void setColor(const Color &newColor);
	
		virtual void receiveMessage(int senderID, int destID, int message, void *data);
	protected:
	    		void setEntity(Entity *newEntity);

	private:
		Color color;
		std::list<std::list<std::list<CharSprite> > > charSpritesLines;
		void resetPosition();
		void internalResetPosition();
		TextureFont * font;
		TextAlignment::type alignment;
		TextComponent* textComponent;
		bool isWordJump(Char32 charCode);
		void lineJump (Vector2 & newLineJump, Vector2 & advance, std::list<CharSprite> &charSpritesForAlignmentAdjust);
		bool needPositionReset;
	};

}

#endif
