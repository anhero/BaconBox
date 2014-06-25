#ifndef BB_DEFAULT_AABBHITBOX_H
#define BB_DEFAULT_AABBHITBOX_H

#include "BaconBox/Components/AABBHitBox.h"
#include "BaconBox/Components/Mesh.h"
#include "BaconBox/Components/EntityContainer.h"

namespace BaconBox {

	class DefaultAABBHitBox : public AABBHitBox {
	public:
		DefaultAABBHitBox();
		DefaultAABBHitBox(const DefaultAABBHitBox &src);
		
		DefaultAABBHitBox &operator=(const DefaultAABBHitBox &src);
		
		DefaultAABBHitBox *clone() const;
		
		const AABB &getAABB();
	private:
		void initializeConnections();
		
		Mesh *mesh;
		EntityContainer *entityContainer;
	};
}

#endif // BB_DEFAULT_AABBHITBOX_H
