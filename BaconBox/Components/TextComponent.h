#ifndef BB_TEXTCOMPONENT_H
#define BB_TEXTCOMPONENT_H

#include "BaconBox/Core/Component.h"
#include "BaconBox/Vector2.h"
#include "BaconBox/Core/Entity.h"
#include "BaconBox/AxisAlignedBoundingBox.h"
#include "BaconBox/Display/Text/TextAlignment.h"
namespace BaconBox {
    class TextComponentProxy;
    class Font;

	class TextComponent : public Component {
	    friend class TextComponentProxy;
	public:
		static int MESSAGE_TEXT_CHANGED;
		static int MESSAGE_ALIGNMENT_CHANGED;
		static int MESSAGE_SIZE_CHANGED;
		BB_ID_HEADER;

	
	
		TextComponent();

		virtual ~TextComponent();
		void setAlignment(TextAlignment alignment);
		void setText(const std::string & text);
		void setSize(Vector2 size);
		Vector2 getSize();
		Font * getFont();
		virtual void receiveMessage(int senderID, int destID, int message, void *data);
	private:
		Font * font;
		TextAlignment alignment;
		AxisAlignedBoundingBox boundingBox;
	};


	class TextComponentProxy : public ComponentProxy {
	public:
		TextComponentProxy(Entity *entity, Font * font, bool mustAddComponent = true);
		Font * getFont();
		void setSize(Vector2 size);
		Vector2 getSize();
		void setAlignment(TextAlignment alignment);
		void setText(const std::string & text);
	private:

	};
}

#endif
