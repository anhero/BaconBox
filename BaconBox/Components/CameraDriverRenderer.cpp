#include "CameraDriverRenderer.h"

#include "BaconBox/Core/Engine.h"
#include "BaconBox/Display/Driver/GraphicDriver.h"
#include "BaconBox/Display/Color.h"
#include "BaconBox/Core/IDManager.h"
#include "BaconBox/Components/Transform.h"
#include "BaconBox/Components/ColorTransform.h"
#include "BaconBox/Components/Shake.h"

namespace BaconBox {
	BB_ID_IMPL(CameraDriverRenderer);

	CameraDriverRenderer::CameraDriverRenderer() : Component(), transform(NULL),  colorTransform(NULL), shake(NULL) {
	    this->initializeConnections();
	}

	CameraDriverRenderer::CameraDriverRenderer(const CameraDriverRenderer &src) : Component(src), transform(NULL),  colorTransform(NULL), shake(NULL) {
		this->initializeConnections();
	}

	CameraDriverRenderer::~CameraDriverRenderer() {
	}

	void CameraDriverRenderer::initializeConnections(){
	    this->addConnection(new ComponentConnection<Transform>(&this->transform));
	    this->addConnection(new ComponentConnection<ColorTransform>(&this->colorTransform));
	    this->addConnection(new ComponentConnection<Shake>(&this->shake));
	}

	CameraDriverRenderer &CameraDriverRenderer::operator=(const CameraDriverRenderer &src) {
		this->Component::operator=(src);

		return *this;
	}

	CameraDriverRenderer *CameraDriverRenderer::clone() const {
		return new CameraDriverRenderer(*this);
	}

	void CameraDriverRenderer::update() {
		Engine::getGraphicDriver().prepareScene(this->transform->getPosition() + this->shake->getOffset(), this->transform->getRotation(), this->transform->getScale(), this->colorTransform->getColor(), true);
	}
}
