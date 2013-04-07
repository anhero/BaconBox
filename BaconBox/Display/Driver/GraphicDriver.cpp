#include "BaconBox/Display/Driver/GraphicDriver.h"

#include "BaconBox/Core/Engine.h"
#include "BaconBox/Console.h"
namespace BaconBox {
	GraphicDriver &GraphicDriver::getInstance() {
		return Engine::getGraphicDriver();
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


	TextureInformation *GraphicDriver::loadTexture(PixMap *pixMap) {
		if (!isInitialized()) {
			Console__error("You are trying to load a texture before the GraphicDriver initialization!");
		}

		return NULL;
	}

}
