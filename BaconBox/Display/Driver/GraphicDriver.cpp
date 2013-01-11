#include "BaconBox/Display/Driver/GraphicDriver.h"

#include "BaconBox/Core/Engine.h"

namespace BaconBox {
	GraphicDriver &GraphicDriver::getInstance() {
		return Engine::getGraphicDriver();
	}

	GraphicDriver::GraphicDriver() {
	}

	GraphicDriver::~GraphicDriver() {
	}
}
