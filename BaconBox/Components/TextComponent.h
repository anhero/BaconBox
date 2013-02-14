#ifndef BB_TEXTCOMPONENT_H
#define BB_TEXTCOMPONENT_H

#include "BaconBox/Core/Component.h"
#include "BaconBox/Vector2.h"
#include "BaconBox/Core/Entity.h"

namespace BaconBox {
    class TextComponentProxy;
    class Font;

	class TextComponent : public Component {
	    friend class TextComponentProxy;
	public:
		static int MESSAGE_TEXT_CHANGED;
	    
	    
		BB_ID_HEADER;

	
	
		TextComponent();

		virtual ~TextComponent();
		
		void setText(const std::string & text);
		Font * getFont();
		virtual void receiveMessage(int senderID, int destID, int message, void *data);
	private:
		Font * font;
	    
	};


	class TextComponentProxy : public ComponentProxy {
	public:
		TextComponentProxy(Entity *entity, Font * font, bool mustAddComponent = true);
		Font * getFont();
		void setText(const std::string & text);


	private:

	};
}

#endif
