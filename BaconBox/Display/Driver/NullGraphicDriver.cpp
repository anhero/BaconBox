#include "BaconBox/Display/Driver/NullGraphicDriver.h"

namespace BaconBox {
	NullGraphicDriver &NullGraphicDriver::getInstance() {
		static NullGraphicDriver instance;
		return instance;
	}

    void NullGraphicDriver::deleteTexture(TextureInformation * textureInfo){

    }

	
	
	void NullGraphicDriver::drawShapeWithTextureColorColorOffset(const VertexArray &vertices,
											  const TextureInformation *textureInformation,
											  const TextureCoordinates &textureCoordinates,
											  const Color &color,
																 const Color &colorOffset, bool blend){
		
	}
	
	
	
	void NullGraphicDriver::drawBatchWithTextureColorColorOffset(const VertexArray &vertices,
											  const TextureInformation *textureInformation,
											  const TextureCoordinates &textureCoordinates,
											  const IndiceArray &indices,
											  const ColorArray &colors,
											const ColorArray &colorOffsets, bool blend){
		
	}
	
	
	
	void NullGraphicDriver::drawShapeWithTexture(const VertexArray &vertices,
							  const TextureInformation *textureInformation,
							  const TextureCoordinates &textureCoordinates,
							  bool blend){
		
	}
	
	
	void NullGraphicDriver::drawBatchWithTexture(const VertexArray &vertices,
							  const TextureInformation *textureInformation,
							  const TextureCoordinates &textureCoordinates,
							  const IndiceArray &indices,
							  bool blend){
		
	}
	

	void NullGraphicDriver::prepareScene(const Vector2 &, float,
	                                     const Vector2 &, const Color &, bool ) {
	}


	void NullGraphicDriver::initializeGraphicDriver() {
	}

	void NullGraphicDriver::pushMatrix() {
	}

	void NullGraphicDriver::translate(const Vector2 &) {
	}
	
	void NullGraphicDriver::scale(const Vector2 &scale){}
	void NullGraphicDriver::rotate(float angle){}

	void NullGraphicDriver::loadIdentity() {
	}

	void NullGraphicDriver::popMatrix() {
	}

	TextureInformation *NullGraphicDriver::loadTexture(PixMap *) {
		return NULL;
	}

	void NullGraphicDriver::finalizeRender() {
	}

	NullGraphicDriver::NullGraphicDriver() {
	}

	NullGraphicDriver::~NullGraphicDriver() {
	}
}

