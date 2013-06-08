#include "AABBHitBox.h"

namespace BaconBox {
	BB_ID_IMPL(AABBHitBox);

	AABBHitBox::AABBHitBox(): Component(), haveCustomAABB(false), sizeComponent(NULL), transform(NULL) {
		initializeConnections();
	}

	void AABBHitBox::initializeConnections() {
		this->addConnection(new ComponentConnection<SizeComponent>(&this->sizeComponent));
		this->addConnection(new ComponentConnection<Transform>(&this->transform));
	}

	void AABBHitBox::setAABB(const AxisAlignedBoundingBox &aabb) {
		haveCustomAABB = true;
		customAABB = aabb;
	}

	AABBHitBoxProxy::AABBHitBoxProxy(Entity *entity, bool mustAddComponent): ComponentProxy(entity, NULL) {
	}

	void AABBHitBoxProxy::setAABBHitBox(AABBHitBox *aabbHitBox) {
		component = aabbHitBox;
		entity->addComponent(aabbHitBox);
	}

	const AxisAlignedBoundingBox &AABBHitBoxProxy::getAABB() {
		return reinterpret_cast<AABBHitBox *>(component)->getAABB();
	}

	void AABBHitBoxProxy::setAABB(const AxisAlignedBoundingBox &aabb) {
		reinterpret_cast<AABBHitBox *>(component)->setAABB(aabb);
	}
}
