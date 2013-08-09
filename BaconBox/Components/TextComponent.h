#ifndef BB_TEXTCOMPONENT_H
#define BB_TEXTCOMPONENT_H

#include "BaconBox/Core/Component.h"
#include "BaconBox/Vector2.h"
#include "BaconBox/Property.h"

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
		static int MESSAGE_FONT_CHANGED;
		static int MESSAGE_ALIGNMENT_CHANGED;
		static int MESSAGE_SIZE_CHANGED;
		
		BB_ID_HEADER;

		TextComponent();

		virtual ~TextComponent();
		void setAlignment(TextAlignment::type alignment);
		void setText(const std::string &text);
		const std::string & getText() const;
		void setSize(Vector2 size);
		const Vector2   &getSize();
		void setFont(Font *font);
		Font *getFont();

		virtual void receiveMessage(int senderID, int destID, int message, void *data);
	private:
		std::string text;
		Font *font;
		TextAlignment::type alignment;
		AxisAlignedBoundingBox boundingBox;
	};

	class TextComponentProxy : public ComponentProxy {
	public:
		
#ifdef SWIG
		std::string text;
#else
		Property<const std::string &, TextComponentProxy> text;
#endif
		
		TextComponentProxy(Entity *entity, Font *font, bool mustAddComponent = true);
		Font *getFont();
		void setFont(Font *font);
		void setSize(Vector2 size);
		const Vector2   &getSize();
		void setAlignment(TextAlignment::type alignment);
		void setText(const std::string &text);
		const std::string & getText() const;

	};
}

#endif
