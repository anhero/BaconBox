#include "Camera.h"
#include "BaconBox/Components/CameraDriverRenderer.h"


#ifdef BB_FLASH_PLATEFORM
#include "BaconBox/Components/Flash/FlashColorTransform.h"
#include "BaconBox/Components/Flash/FlashCameraManager.h"
#else
#include "BaconBox/Components/DefaultColorTransform.h"
#endif


namespace BaconBox {
	Camera::Camera() : Entity(), TransformProxy(this), ColorTransformProxy(this)  {
	    #ifdef BB_FLASH_PLATEFORM
                setColorTransform(new FlashColorTransform());
                addComponent(new FlashCameraManager());
        #else
                setColorTransform(new DefaultColorTransform());
                addComponent(new CameraDriverRenderer());

        #endif
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
