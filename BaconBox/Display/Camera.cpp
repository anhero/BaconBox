#include "Camera.h"

#include "BaconBox/Components/CameraDriverRenderer.h"
namespace BaconBox {
	
	Camera::Camera(){
		addComponent(new CameraDriverRenderer());
		
	}
	
    
}