#ifndef BB_AABBHITBOX_H
#define BB_AABBHITBOX_H

#include "BaconBox/AABB.h"
#include "BaconBox/Core/Component.h"
#include "BaconBox/Vector2.h"
#include "BaconBox/Core/Entity.h"
#include "BaconBox/Components/SizeComponent.h"
#include "BaconBox/Components/Transform.h"
#include "BaconBox/Components/ComponentConnection.h"

namespace BaconBox {
	/**
	 * The AABBHitBox component determines the entity's bounding box used
	 * for collision detection.
	 */
	class AABBHitBox : public Component {
	public:
		BB_ID_HEADER;
		AABBHitBox();
		AABBHitBox(const AABBHitBox &src);
		
		AABBHitBox &operator=(const AABBHitBox &src);
		
		virtual const AABB &getAABB() = 0;
		void setAABB(const AABB &aabb);
	protected:
		bool haveCustomAABB;
		AABB customAABB;

		SizeComponent *sizeComponent;
		Transform *transform;
	private:
		void initializeConnections();
	};

	class AABBHitBoxProxy : public ComponentProxy {
	public:
		AABBHitBoxProxy(Entity *entity, bool mustAddComponent = true);
		const AABB &getAABB();
		void setAABB(const AABB &aabb);

	protected:
		void setAABBHitBox(AABBHitBox *aabbHitBox);

	};

}

#endif // BB_AABBHITBOX_H
