#ifndef BB_TEXTRENDERER_H
#define BB_TEXTRENDERER_H

#include "BaconBox/Core/Component.h"
#include "BaconBox/Vector2.h"
#include "BaconBox/Core/Entity.h"
#include "BaconBox/Display/Text/TextureFont.h"

#include "BaconBox/MovieClipEntity/MovieClipEntity.h"
namespace BaconBox {
    class TextRendererProxy;
	/**
	 * Component that manages the entity's position, orientation and scaling
	 * values.
	 */
	class TextRenderer : public Component {
	    friend class TextRendererProxy;
	public:
		BB_ID_HEADER;

	
		/**
		 * Default constructor.
		 */
		TextRenderer();
		
		virtual void render();

		/**
		 * Destructor.
		 */
		virtual ~TextRenderer();
		
		void setText(std::string text);


		/**
		 * Handles the messages received.
		 * @param senderID Type ID of component/entity sending the message.
		 * @param destID Type ID of the component/entity the message is
		 * destined to.
		 * @param data Data used to send or receive any data related to the
		 * message.
		 */
		virtual void receiveMessage(int senderID, int destID, int message, void *data);
	private:
	    std::list<MovieClipEntity*> sprites;
	    TextureFont * font;
	    
	};


	class TextRendererProxy : public ComponentProxy {
	public:
		TextRendererProxy(Entity *entity, TextureFont * font, bool mustAddComponent = true);

		void setText(std::string text);


	private:

	};
}

#endif
