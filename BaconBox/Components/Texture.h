#ifndef BB_TEXTURE_H
#define BB_TEXTURE_H

#include "BaconBox/Core/Component.h"
#include "BaconBox/TextureCoordinates.h"

namespace BaconBox {
	struct TextureInformation;
	
	/**
	 * Contains the information about an entity's texture.
	 */
	class Texture : public Component {
	public:
		static int MESSAGE_GET_TEXTURE;
		static int MESSAGE_SET_TEXTURE;
		
		static int MESSAGE_GET_TEXTURE_COORDINATES;
		static int MESSAGE_SET_TEXTURE_COORDINATES;
		
		Texture();
		
		Texture(const Texture &src);
		
		virtual ~Texture();
		
		Texture &operator=(const Texture &src);
		
		virtual Texture *clone() const;
		
		virtual void receiveMessage(int senderID, int destID, int message, void *data);
		
		TextureInformation *getTexture() const;
		void setTexture(TextureInformation *newTexture);
		
		const TextureCoordinates &getTextureCoordinates() const;
		TextureCoordinates &getTextureCoordinates();
		void setTextureCoordinates(TextureCoordinates &newTextureCoordinates);
	private:
		/// Pointer to the entity's texture information.
		TextureInformation *texture;
		
		/// Contains the entity's texture coordinates.
		TextureCoordinates textureCoordinates;
	};
}

#endif /* defined(BB_TEXTURE_H) */

