#ifndef BB_SIZECOMPONENT_H
#define BB_SIZECOMPONENT_H

#include "BaconBox/Core/Component.h"
#include "BaconBox/Vector2.h"
#include "BaconBox/Core/Entity.h"
namespace BaconBox {

class SizeComponent : public Component {
    public:
    	BB_ID_HEADER;
        SizeComponent();
        virtual float getWidth() = 0;
        virtual float getHeight() = 0;
        virtual Vector2 getSize();
    protected:
    private:
};


	class SizeComponentProxy : public ComponentProxy {
	public:
		SizeComponentProxy(Entity *entity);
		float getWidth();
		float getHeight();
		Vector2 getSize();

	protected:
	    	void setSizeComponent(SizeComponent * sizeComponent);

	};
}

#endif // BB_SIZECOMPONENT_H
