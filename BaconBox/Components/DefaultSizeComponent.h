#ifndef BB_DEFAULT_SIZECOMPONENT_H
#define BB_DEFAULT_SIZECOMPONENT_H

#include "BaconBox/Components/SizeComponent.h"
#include "BaconBox/Components/AABBHitBox.h"


namespace BaconBox {
	/**
	 * The SizeComponent determines the width and height of an entity.
	 */
	class DefaultSizeComponent : public SizeComponent {
	public:
		DefaultSizeComponent();
		float getWidth();
		float getHeight();
		
	private:
		void initializeConnections();
		AABBHitBox * aabb;
	};


}

#endif // BB_SIZECOMPONENT_H
