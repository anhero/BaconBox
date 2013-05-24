#include "BaconBox/Display/Driver/NullGraphicDriver.h"

namespace BaconBox {
	NullGraphicDriver &NullGraphicDriver::getInstance() {
		static NullGraphicDriver instance;
		return instance;
	}

	void NullGraphicDriver::drawShapeWithTextureAndColor(const VertexArray &,
	                                                     const TextureInformation *,
	                                                     const TextureCoordinates &,
	                                                     const Color &) {
	}

	void NullGraphicDriver::drawShapeWithTextureAndColorTransform(const VertexArray &vertices,
              const TextureInformation *textureInformation,
              const TextureCoordinates &textureCoordinates,
              const Color &color,
              const ColorTransformArray &colorMultiplier,
              const ColorTransformArray &colorOffset){
              }

	void NullGraphicDriver::drawShapeWithTexture(const VertexArray &,
	                                             const TextureInformation *,
	                                             const TextureCoordinates &) {
	}

	void NullGraphicDriver::drawShapeWithColor(const VertexArray &,
	                                           const Color &) {
	}

	void NullGraphicDriver::drawBatchWithTextureAndColorTransform(const VertexArray &vertices,
		                                  const TextureInformation *textureInformation,
		                                  const TextureCoordinates &textureCoordinates,
		                                  const IndiceArray &indices,
		                                  const IndiceArrayList &indiceList,
		                                  const ColorArray &colors,
		                                  const ColorTransformArray &colorMultipliers,
		                                  const ColorTransformArray &colorOffsets){


		                                  }


	void NullGraphicDriver::drawBatchWithTextureAndColor(const VertexArray &,
	                                                     const TextureInformation *,
	                                                     const TextureCoordinates &,
	                                                     const IndiceArray &,
	                                                     const IndiceArrayList &,
	                                                     const ColorArray &) {
	}

	void NullGraphicDriver::drawBatchWithTexture(const VertexArray &,
	                                             const TextureInformation *,
	                                             const TextureCoordinates &,
	                                             const IndiceArray &,
	                                             const IndiceArrayList &) {
	}

    void NullGraphicDriver::deleteTexture(TextureInformation * textureInfo){

    }



	void NullGraphicDriver::prepareScene(const Vector2 &, float,
	                                     const Vector2 &, const Color &) {
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

