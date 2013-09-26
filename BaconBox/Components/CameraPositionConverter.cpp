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
	
	
	const Vector2 CameraPositionConverter::screenToWorld(const Vector2 &positionOnScreen) const{
				
		// We apply the camera's scaling and rotation to the position on screen.
		
		
		// We apply the camera's scaling and rotation to the position on screen.
		Vector2 result(positionOnScreen);
		
		
		result +=(transform->getPosition());
		result.rotate(-(transform->getRotation()));
		
		Vector2 v(1, 1);
		
		v.coordinatesDivide(transform->getScale());
		result.coordinatesMultiply(v);
		
		
	
		
		return result;
	}
	
	
	const Vector2 CameraPositionConverter::worldToScreen(const Vector2 &positionInWorld) const{
		Vector2 result(positionInWorld - transform->getPosition() );
		
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

	const Vector2 CameraPositionConverterProxy::screenToWorld(const Vector2 &positionOnScreen) const{
		return reinterpret_cast<CameraPositionConverter *>(component)->screenToWorld(positionOnScreen);
	}
	
	
	const Vector2 CameraPositionConverterProxy::worldToScreen(const Vector2 &positionInWorld) const{
		return reinterpret_cast<CameraPositionConverter *>(component)->worldToScreen(positionInWorld);
	}
	


}
