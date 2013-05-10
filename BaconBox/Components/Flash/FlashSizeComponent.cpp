#include "FlashSizeComponent.h"

using namespace BaconBox;

FlashSizeComponent::FlashSizeComponent(): SizeComponent(){
		    initializeConnections();
}


void FlashSizeComponent::initializeConnections(){
	    this->addConnection(new ComponentConnection<MovieClipHolder>(&this->movieClipHolder));
	    this->refreshConnections();
}

float FlashSizeComponent::getWidth(){
	return AS3::local::internal::double_valueOf(movieClipHolder->getProperty("width"));
}
float FlashSizeComponent::getHeight(){
	return AS3::local::internal::double_valueOf(movieClipHolder->getProperty("height"));
}

