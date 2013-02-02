#include "Camera.h"

#include "BaconBox/Components/CameraDriverRenderer.h"
namespace BaconBox {
	Camera::Camera() : Entity() {
		addComponent(new CameraDriverRenderer());
	}

	Camera::~Camera() {
	}
	
	Camera &Camera::operator=(const Camera &src) {
		this->Entity::operator=(src);
		
		return *this;
	}
	
	Camera *Camera::clone() const {
		return new Camera(*this);
	}
}