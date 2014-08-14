#include "BaconBox/Display/Driver/GraphicDriver.h"

#include "BaconBox/Core/Engine.h"
#include "BaconBox/Console.h"

#include BB_GRAPHIC_DRIVER_INCLUDE

namespace BaconBox {

	GraphicDriver &GraphicDriver::getInstance() {
		return * static_cast<GraphicDriver *>(BB_GRAPHIC_DRIVER_IMPL);
	}

	GraphicDriver::GraphicDriver(): initialized(false) {
	}

	GraphicDriver::~GraphicDriver() {
	}

	void GraphicDriver::initializeGraphicDriver() {
		initialized = true;
	}

	bool GraphicDriver::isInitialized() {
		return initialized;
	}


	TextureInformation *GraphicDriver::loadTexture(PixMap *pixMap, TextureInformation *textureInfo) {
		if (!isInitialized()) {
			Console__error("You are trying to load a texture before the GraphicDriver initialization!");
		}

		return NULL;
	}

}
