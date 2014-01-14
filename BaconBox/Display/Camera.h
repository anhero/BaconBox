/**
 * @file
 */
#ifndef BB_CAMERA_H
#define BB_CAMERA_H
#include "BaconBox/PlatformFlagger.h"

#include "BaconBox/Core/Entity.h"
#include "BaconBox/Components/Transform.h"
#include "BaconBox/Components/ColorTransform.h"
#include "BaconBox/Components/Shake.h"
#include "BaconBox/Components/MatrixComponent.h"
#include "BaconBox/Components/CameraPositionConverter.h"
#ifdef BB_LUA
#include "BaconBox/Components/Lua/LuaEntity.h"
#endif
namespace BaconBox {
	/**
	 * Represents a camera. Its position determines what the player sees on his
	 * screen.
	 */
	class Camera : public Entity, public TransformProxy, public ColorTransformProxy, public MatrixComponentProxy, public ShakeProxy, public CameraPositionConverterProxy
#ifdef BB_LUA
	, public LuaEntityProxy
#endif //BB_LUA
	{
    public:
		Camera();

		virtual ~Camera();

		Camera &operator=(const Camera &src);

		virtual Camera *clone() const;
    private:

	};
}

#endif // BB_CAMERA_H
