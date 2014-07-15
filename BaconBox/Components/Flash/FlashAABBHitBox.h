#ifndef BB_FLASH_AABBHITBOX_H
#define BB_FLASH_AABBHITBOX_H

#include "BaconBox/Components/AABBHitBox.h"
#include "BaconBox/Components/Flash/MovieClipHolder.h"

#include <AS3/AS3.h>
#include <AS3/AS3++.h>

namespace BaconBox {

	class FlashAABBHitBox : public AABBHitBox {
	public:
		FlashAABBHitBox();
		const AABB &getAABB();
	private:
		void initializeConnections();
		MovieClipHolder *movieClipHolder;
		AS3::local::var stage;

	};
}

#endif // BB_FLASH_AABBHITBOX_H
