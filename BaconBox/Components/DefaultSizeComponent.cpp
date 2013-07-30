#include "DefaultSizeComponent.h"
#include "BaconBox/Components/ComponentConnection.h"
namespace BaconBox {

	DefaultSizeComponent::DefaultSizeComponent(): SizeComponent(), aabb(NULL) {
		this->initializeConnections();
	}

	DefaultSizeComponent::DefaultSizeComponent(const DefaultSizeComponent &src) : SizeComponent(src), aabb(NULL) {
		this->initializeConnections();
	}

	DefaultSizeComponent &DefaultSizeComponent::operator=(const DefaultSizeComponent &src) {
		this->SizeComponent::operator=(src);

		return *this;
	}

	DefaultSizeComponent *DefaultSizeComponent::clone() const {
		return new DefaultSizeComponent(*this);
	}

	float DefaultSizeComponent::getWidth() const {
		return aabb->getAABB().getSize().x;
	}
	float DefaultSizeComponent::getHeight() const {
		return aabb->getAABB().getSize().y;
	}

	void DefaultSizeComponent::initializeConnections() {
		this->addConnection(new ComponentConnection<AABBHitBox>(&this->aabb));
		this->refreshConnections();
	}
}