#include "CameraDriverRenderer.h"

#include "BaconBox/Core/Engine.h"
#include "BaconBox/Display/Driver/GraphicDriver.h"
#include "BaconBox/Display/Color.h"
#include "BaconBox/Core/IDManager.h"

namespace BaconBox {
	BB_ID_IMPL(CameraDriverRenderer);

	CameraDriverRenderer::CameraDriverRenderer() : Component(), transform(NULL),  colorTransform(NULL){
	    initializeConnections();
	}

	CameraDriverRenderer::CameraDriverRenderer(const CameraDriverRenderer &src) : Component(src) {
	}

	CameraDriverRenderer::~CameraDriverRenderer() {
	}

	void CameraDriverRenderer::initializeConnections(){
	    this->addConnection(new ComponentConnection<Transform>(&this->transform));
	    this->addConnection(new ComponentConnection<ColorTransform>(&this->colorTransform));
	}

	CameraDriverRenderer &CameraDriverRenderer::operator=(const CameraDriverRenderer &src) {
		this->Component::operator=(src);

		return *this;
	}

	CameraDriverRenderer *CameraDriverRenderer::clone() const {
		return new CameraDriverRenderer(*this);
	}

	void CameraDriverRenderer::receiveMessage(int senderID, int id, int message, void *data) {
	    Component::receiveMessage(senderID, id,message,data);
	}

	void CameraDriverRenderer::update() {
	}

	void CameraDriverRenderer::render(){
		Engine::getGraphicDriver().prepareScene(transform->getPosition(), transform->getRotation()*-1, transform->getScale(), colorTransform->getColor());
	}
}
