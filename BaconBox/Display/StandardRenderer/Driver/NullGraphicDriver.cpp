#include "BaconBox/Display/StandardRenderer/Driver/NullGraphicDriver.h"
#include "BaconBox/Core/Engine.h"

namespace BaconBox {

	BB_SINGLETON_IMPL(NullGraphicDriver)
	
	void NullGraphicDriver::renderToTexture(const TextureInformation *textureInformation, unsigned int viewportWidth, unsigned int viewportHeight, unsigned int contextWidth, unsigned int contextHeight){}
	void NullGraphicDriver::endRenderToTexture(){}
	
	void NullGraphicDriver::drawShapeWithTextureColorColorOffset(const VertexArray &vertices,
											  const TextureInformation *textureInformation,
											  const TextureCoordinates &textureCoordinates,
											  const Color &color,
																 const Color &colorOffset, bool blend, int degenerationStride, int degenerationJump){
		
	}
	
	
	
	void NullGraphicDriver::drawBatchWithTextureColorColorOffset(const VertexArray &vertices,
											  const TextureInformation *textureInformation,
											  const TextureCoordinates &textureCoordinates,
											  const IndiceArray &indices,
											  const ColorArray &colors,
											const ColorArray &colorOffsets, bool blend){
		
	}
	
	void NullGraphicDriver::resetProjection(){
		
	}

		void NullGraphicDriver::tearGraphicDriver(){
			
		}
	
	void NullGraphicDriver::drawShapeWithTexture(const VertexArray &vertices,
							  const TextureInformation *textureInformation,
							  const TextureCoordinates &textureCoordinates,
							  bool blend, int degenerationStride, int degenerationJump){
		
	}
	
	
	void NullGraphicDriver::drawBatchWithTexture(const VertexArray &vertices,
							  const TextureInformation *textureInformation,
							  const TextureCoordinates &textureCoordinates,
							  const IndiceArray &indices,
							  bool blend){
		
	}
	
    void NullGraphicDriver::drawShapeWithColorColorOffset(const VertexArray &vertices,
                                              const Color &color,
                                              const Color &colorOffset,
                                              bool blend, int degenerationStride, int degenerationJump) {
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

	TextureInformation *NullGraphicDriver::loadTexture(PixMap *, TextureInformation *) {
		return NULL;
	}

	void NullGraphicDriver::finalizeRender() {
	}

	NullGraphicDriver::NullGraphicDriver() {
	}

	NullGraphicDriver::~NullGraphicDriver() {
	}
}

