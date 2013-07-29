#ifndef BB_CAMERAPOSITIONCONVERTER_H
#define BB_CAMERAPOSITIONCONVERTER_H

#include "BaconBox/Core/Component.h"
#include "BaconBox/Vector2.h"

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
		const Vector2 screenToWorld(const Vector2 &positionOnScreen) const;
		const Vector2 worldToScreen(const Vector2 &positionInWorld) const;
		
	protected:
		void initializeConnections();
		
		
		
		
	private:
		Transform *transform;
	};
	
	class CameraPositionConverterProxy : public ComponentProxy {
	public:
		CameraPositionConverterProxy(Entity *entity, bool mustAddComponent = true);
		
		const Vector2 screenToWorld(const Vector2 &positionOnScreen) const;
		const Vector2 worldToScreen(const Vector2 &positionInWorld) const;
	protected:
	};
}

#endif
