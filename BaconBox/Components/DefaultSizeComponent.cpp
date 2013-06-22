#include "DefaultSizeComponent.h"
#include "BaconBox/Components/ComponentConnection.h"
using namespace BaconBox;

DefaultSizeComponent::DefaultSizeComponent(): SizeComponent(), aabb(NULL){
	initializeConnections();
}



float DefaultSizeComponent::getWidth(){
	return aabb->getAABB().getSize().x;
}
float DefaultSizeComponent::getHeight(){
	return aabb->getAABB().getSize().y;
}

void DefaultSizeComponent::initializeConnections(){
	this->addConnection(new ComponentConnection<AABBHitBox>(&this->aabb));
	this->refreshConnections();
}
