#ifndef BB_AABBHITBOX_H
#define BB_AABBHITBOX_H

#include "BaconBox/AxisAlignedBoundingBox.h"
#include "BaconBox/Core/Component.h"
#include "BaconBox/Vector2.h"
#include "BaconBox/Core/Entity.h"
#include "BaconBox/Components/SizeComponent.h"
#include "BaconBox/Components/Transform.h"
#include "BaconBox/Components/ComponentConnection.h"

namespace BaconBox {

class AABBHitBox : public Component {
    public:
    	BB_ID_HEADER;
        AABBHitBox();
        virtual const AxisAlignedBoundingBox & getAABB() = 0;
        void setAABB(const AxisAlignedBoundingBox & aabb);
    protected:
        bool haveCustomAABB;
        AxisAlignedBoundingBox customAABB;

        SizeComponent * sizeComponent;
        Transform * transform;
        void initializeConnections();
    private:
};

class AABBHitBoxProxy : public ComponentProxy {
	public:
		AABBHitBoxProxy(Entity *entity, bool mustAddComponent = true);
		const AxisAlignedBoundingBox & getAABB();
        void setAABB(const AxisAlignedBoundingBox & aabb);

	protected:
	    	void setAABBHitBox(AABBHitBox * aabbHitBox);

	};

}

#endif // BB_AABBHITBOX_H
