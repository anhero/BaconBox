#ifndef BB_DEFAULT_SIZE_COMPONENT_H
#define BB_DEFAULT_SIZE_COMPONENT_H

#include "BaconBox/Components/SizeComponent.h"
#include "BaconBox/Components/AABBHitBox.h"


namespace BaconBox {
	/**
	 * The SizeComponent determines the width and height of an entity.
	 */
	class DefaultSizeComponent : public SizeComponent {
	public:
		DefaultSizeComponent();

		DefaultSizeComponent(const DefaultSizeComponent &src);

		DefaultSizeComponent &operator=(const DefaultSizeComponent &src);

		DefaultSizeComponent *clone() const;
		
		float getWidth() const;
		float getHeight() const;

	private:
		void initializeConnections();
		AABBHitBox *aabb;
	};


}

#endif // BB_SIZE_COMPONENT_H
