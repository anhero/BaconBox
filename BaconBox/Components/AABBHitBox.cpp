#include "AABBHitBox.h"

namespace BaconBox {
	BB_ID_IMPL(AABBHitBox);

	AABBHitBox::AABBHitBox(): Component(), haveCustomAABB(false), customAABB(), sizeComponent(NULL), transform(NULL) {
		this->initializeConnections();
	}

	AABBHitBox::AABBHitBox(const AABBHitBox &src) : Component(src), haveCustomAABB(src.haveCustomAABB), customAABB(src.customAABB), sizeComponent(NULL), transform(NULL) {
		this->initializeConnections();
	}

	AABBHitBox &AABBHitBox::operator=(const AABBHitBox &src) {
		this->Component::operator=(src);

		if (this != &src) {
			this->haveCustomAABB = src.haveCustomAABB;
			this->customAABB = src.customAABB;
		}

		return *this;
	}

	void AABBHitBox::initializeConnections() {
		this->addConnection(new ComponentConnection<SizeComponent>(&this->sizeComponent));
		this->addConnection(new ComponentConnection<Transform>(&this->transform));
	}

	void AABBHitBox::setAABB(const AxisAlignedBoundingBox &aabb) {
		this->haveCustomAABB = true;
		this->customAABB = aabb;
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
