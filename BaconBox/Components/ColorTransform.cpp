#include "ColorTransform.h"

#include "BaconBox/Core/IDManager.h"
#include "BaconBox/Core/Entity.h"
#include "BaconBox/Console.h"
namespace BaconBox {
	BB_ID_IMPL(ColorTransform);


	ColorTransform::ColorTransform() : Component(){
	}



	ColorTransformProxy::ColorTransformProxy(Entity *entity): ComponentProxy(entity, NULL)  {
	}

	void ColorTransformProxy::setAlpha(uint8_t alpha){
		reinterpret_cast<ColorTransform*>(component)->setAlpha(alpha);
	}

	ColorMatrix &  ColorTransformProxy::getConcatColorMatrix(){
		return reinterpret_cast<ColorTransform*>(component)->getConcatColorMatrix();
	}



	void ColorTransformProxy::setColorTransform(ColorTransform * colorTransform){
		component = colorTransform;
	    entity->addComponent(component);
	}

}
