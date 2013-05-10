#include "SizeComponent.h"

using namespace BaconBox;
BB_ID_IMPL(SizeComponent);

SizeComponent::SizeComponent(): Component(){
}


Vector2 SizeComponent::getSize(){
	return Vector2(getWidth(), getHeight());
}

SizeComponentProxy::SizeComponentProxy(Entity *entity) : ComponentProxy(entity, NULL) {
		
}

	 
	    
void SizeComponentProxy::setSizeComponent(SizeComponent * sizeComponent){
	component = sizeComponent;
	entity->addComponent(sizeComponent);	
}

float SizeComponentProxy::getWidth(){
		 return reinterpret_cast<SizeComponent*>(component)->getWidth();
}
float SizeComponentProxy::getHeight(){
		 return reinterpret_cast<SizeComponent*>(component)->getHeight();
}
Vector2 SizeComponentProxy::getSize(){
		 return reinterpret_cast<SizeComponent*>(component)->getSize();
}