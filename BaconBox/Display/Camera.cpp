#include "Camera.h"
#include "BaconBox/Components/CameraDriverRenderer.h"


#ifdef BB_FLASH_PLATFORM
#include "BaconBox/Components/Flash/FlashColorTransform.h"
#include "BaconBox/Components/Flash/FlashCameraManager.h"
#else
#include "BaconBox/Components/DefaultColorTransform.h"
#endif

#include "BaconBox/Components/DefaultMatrix.h"
namespace BaconBox {
	Camera::Camera() : Entity(), TransformProxy(this), ColorTransformProxy(this), MatrixComponentProxy(this)  {
	    #ifdef BB_FLASH_PLATFORM
                setColorTransform(new FlashColorTransform());
                addComponent(new FlashCameraManager());
        #else
                setColorTransform(new DefaultColorTransform());
                addComponent(new CameraDriverRenderer());

        #endif
		
		
		setMatrixComponent(new DefaultMatrix());

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
