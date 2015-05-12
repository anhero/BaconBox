#ifndef BB_CAMERAPOSITIONCONVERTER_H
#define BB_CAMERAPOSITIONCONVERTER_H

#include "BaconBox/Core/Component.h"
#include "BaconBox/vmath.h"

namespace BaconBox {
	class Transform;
	/**
	 * Component that manages the entity's position, orientation and scaling
	 * values.
	 */
	class CameraPositionConverter : public Component {
	public:
		BB_ID_HEADER;
		CameraPositionConverter();
		const VMATH_NAMESPACE::Vector2f screenToWorld(const VMATH_NAMESPACE::Vector2f &positionOnScreen) const;
		const VMATH_NAMESPACE::Vector2f worldToScreen(const VMATH_NAMESPACE::Vector2f &positionInWorld) const;
		
	protected:
		void initializeConnections();
		
		
		
		
	private:
		Transform *transform;
	};
	
	class CameraPositionConverterProxy : public ComponentProxy {
	public:
		CameraPositionConverterProxy(Entity *entity, bool mustAddComponent = true);
		
		const VMATH_NAMESPACE::Vector2f screenToWorld(const VMATH_NAMESPACE::Vector2f &positionOnScreen) const;
		const VMATH_NAMESPACE::Vector2f worldToScreen(const VMATH_NAMESPACE::Vector2f &positionInWorld) const;
	protected:
	};
}

#endif
