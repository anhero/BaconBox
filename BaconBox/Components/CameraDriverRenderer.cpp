#include "CameraDriverRenderer.h"

#include "BaconBox/Core/Engine.h"
#include "BaconBox/Display/Driver/GraphicDriver.h"
#include "BaconBox/Display/Color.h"

namespace BaconBox {
	
	void CameraDriverRenderer::render(){
		Engine::getGraphicDriver().prepareScene(Vector2(), 0, Vector2(1,1), Color::BLACK);
	}
    
}