#include "Texture.h"

#include "BaconBox/Core/IDManager.h"

namespace BaconBox {
	int Texture::MESSAGE_GET_TEXTURE = IDManager::generateID();
	int Texture::MESSAGE_SET_TEXTURE = IDManager::generateID();
	int Texture::MESSAGE_GET_TEXTURE_COORDINATES = IDManager::generateID();
	int Texture::MESSAGE_SET_TEXTURE_COORDINATES = IDManager::generateID();
	
	Texture::Texture() : Component(), texture(NULL), textureCoordinates() {
	}
	
	Texture::Texture(const Texture &src) : Component(src), texture(src.texture), textureCoordinates(src.textureCoordinates) {
	}
	
	Texture::~Texture() {
	}
	
	Texture &Texture::operator=(const Texture &src) {
		if (this != &src) {
			this->texture = src.texture;
			this->textureCoordinates = src.textureCoordinates;
		}
		
		return *this;
	}
	
	Texture *Texture::clone() const {
		return new Texture(*this);
	}
	
	void Texture::receiveMessage(int senderID, int destID, int message, void *data) {
		if (destID != Texture::ID) {
			return;
		}
		
		if (message == Texture::MESSAGE_GET_TEXTURE) {
			*reinterpret_cast<TextureInformation **>(data) = this->getTexture();
		} else if (message == Texture::MESSAGE_SET_TEXTURE) {
			this->setTexture(*reinterpret_cast<TextureInformation **>(data));
		} else if (message == Texture::MESSAGE_GET_TEXTURE_COORDINATES) {
			*reinterpret_cast<TextureCoordinates*>(data) = this->getTextureCoordinates();
		} else if (message == Texture::MESSAGE_SET_TEXTURE_COORDINATES) {
			this->setTextureCoordinates(*reinterpret_cast<TextureCoordinates *>(data));
		}
	}
	
	TextureInformation *Texture::getTexture() const {
		return this->texture;
	}
	
	void Texture::setTexture(TextureInformation *newTexture) {
		this->texture = newTexture;
	}
	
	const TextureCoordinates &Texture::getTextureCoordinates() const {
		return this->textureCoordinates;
	}
	
	TextureCoordinates &Texture::getTextureCoordinates() {
		return this->textureCoordinates;
	}
	
	void Texture::setTextureCoordinates(TextureCoordinates &newTextureCoordinates) {
		this->textureCoordinates = newTextureCoordinates;
	}
}
