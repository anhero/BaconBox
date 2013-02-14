#ifndef BB_TEXTRENDERER_H
#define BB_TEXTRENDERER_H

#include "BaconBox/Core/Component.h"
#include "BaconBox/Vector2.h"
#include "BaconBox/Core/Entity.h"

#include "BaconBox/MovieClipEntity/MovieClipEntity.h"
namespace BaconBox {
    class TextureFont;
    struct CharSprite;

	class TextRenderer : public Component {
	public:
		BB_ID_HEADER;

	
	
		TextRenderer(TextureFont * font);
		
		virtual void render();

	
		virtual ~TextRenderer();
		
		void setText(const std::string & text);

	
		virtual void receiveMessage(int senderID, int destID, int message, void *data);
	private:
		std::list<CharSprite> charSprites;
		void resetPosition();
		TextureFont * font;
	    
	};

}

#endif
