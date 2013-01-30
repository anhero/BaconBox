#include "CameraDriverRenderer.h"

#include "BaconBox/Core/Engine.h"
#include "BaconBox/Display/Driver/GraphicDriver.h"
#include "BaconBox/Display/Color.h"
#include "BaconBox/Core/IDManager.h"

namespace BaconBox {
	BB_ID_IMPL(CameraDriverRenderer);
	
	CameraDriverRenderer::CameraDriverRenderer() : Component() {
	}
	
	CameraDriverRenderer::CameraDriverRenderer(const CameraDriverRenderer &src) : Component(src) {
	}
	
	CameraDriverRenderer::~CameraDriverRenderer() {
	}
	
	CameraDriverRenderer &CameraDriverRenderer::operator=(const CameraDriverRenderer &src) {
		this->Component::operator=(src);
		
		return *this;
	}
	
	CameraDriverRenderer *CameraDriverRenderer::clone() const {
		return new CameraDriverRenderer(*this);
	}
	
	void CameraDriverRenderer::receiveMessage(int id, int message, void *data) {
	}
	
	void CameraDriverRenderer::update() {
	}
	
	void CameraDriverRenderer::render(){
		Engine::getGraphicDriver().prepareScene(Vector2(), 0, Vector2(1,1), Color::BLUE);
	}
    
}
