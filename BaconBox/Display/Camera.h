/**
 * @file
 */
#ifndef BB_CAMERA_H
#define BB_CAMERA_H
#include "BaconBox/PlatformFlagger.h"

#include "BaconBox/Core/Entity.h"
#include "BaconBox/Components/Transform.h"
#include "BaconBox/Components/ColorTransform.h"

#include "BaconBox/Components/MatrixComponent.h"

namespace BaconBox {
	/**
	 * Represents a camera. Its position determines what the player sees on his
	 * screen.
	 */
	class Camera  : public Entity, public TransformProxy, public  ColorTransformProxy, public MatrixComponentProxy{
    public:
		Camera();

		virtual ~Camera();

		Camera &operator=(const Camera &src);

		virtual Camera *clone() const;
    private:

	};
}

#endif // BB_CAMERA_H
