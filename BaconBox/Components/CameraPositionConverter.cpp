#include "CameraPositionConverter.h"

#include "BaconBox/Core/Entity.h"
#include "BaconBox/Console.h"
#include "BaconBox/Helper/MathHelper.h"
#include "BaconBox/Components/Transform.h"
#include "BaconBox/Components/DefaultMatrix.h"
#include "BaconBox/Display/Window/MainWindow.h"
namespace BaconBox {
	BB_ID_IMPL(CameraPositionConverter);
	
	CameraPositionConverter::CameraPositionConverter() : transform(NULL) {
		initializeConnections();
	}


	void CameraPositionConverter::initializeConnections() {
		this->addConnection(new ComponentConnection<Transform>(&this->transform));
		this->refreshConnections();
	}
	
	
	const VMATH_NAMESPACE::Vector2f CameraPositionConverter::screenToWorld(const VMATH_NAMESPACE::Vector2f &positionOnScreen) const{
				
		// We apply the camera's scaling and rotation to the position on screen.
		
		
		// We apply the camera's scaling and rotation to the position on screen.
		VMATH_NAMESPACE::Vector2f result(positionOnScreen);
		
		VMATH_NAMESPACE::Matrix3 matrix = VMATH_NAMESPACE::Matrix3();
		matrix*=result;
		result +=(transform->getPosition());
		result.rotate(-(transform->getRotation()));
		
		VMATH_NAMESPACE::Vector2f v(1, 1);
		
		v.coordinatesDivide(transform->getScale());
		result.coordinatesMultiply(v);
		
		
	
		
		return result;
	}
	
	
	const VMATH_NAMESPACE::Vector2f CameraPositionConverter::worldToScreen(const VMATH_NAMESPACE::Vector2f &positionInWorld) const{
		VMATH_NAMESPACE::Vector2f result(positionInWorld - transform->getPosition() );
		
		Console::error("CameraPositionConverter::worldToScreen is not implemented yet.");
		
//		Vector2 v(MainWindow::getInstance().getContextWidth(), MainWindow::getInstance().getContextHeight());
//		
//		v.coordinatesDivide(transform->getScale());
//		
//		v.coordinatesDivide(Vector2(static_cast<float>(MainWindow::getInstance().getResolutionWidth()), static_cast<float>(MainWindow::getInstance().getResolutionHeight())));
//		result.coordinatesDivide(v);
//
//		result.rotate(transform->getRotation());
//		
		return result;
	}

	
	CameraPositionConverterProxy::CameraPositionConverterProxy(Entity *entity, bool mustAddComponent): BB_PROXY_CONSTRUCTOR(new CameraPositionConverter())  {
	}

	const VMATH_NAMESPACE::Vector2f CameraPositionConverterProxy::screenToWorld(const VMATH_NAMESPACE::Vector2f &positionOnScreen) const{
		return reinterpret_cast<CameraPositionConverter *>(component)->screenToWorld(positionOnScreen);
	}
	
	
	const VMATH_NAMESPACE::Vector2f CameraPositionConverterProxy::worldToScreen(const VMATH_NAMESPACE::Vector2f &positionInWorld) const{
		return reinterpret_cast<CameraPositionConverter *>(component)->worldToScreen(positionInWorld);
	}
	


}
