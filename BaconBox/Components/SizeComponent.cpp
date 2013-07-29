#include "SizeComponent.h"

namespace BaconBox {
	BB_ID_IMPL(SizeComponent);
	
	SizeComponent::SizeComponent(): Component() {
	}
	
	SizeComponent::SizeComponent(const SizeComponent &src) : Component(src) {
	}
	
	SizeComponent &SizeComponent::operator=(const SizeComponent &src) {
		this->Component::operator=(src);
		
		return *this;
	}
	
	const Vector2 SizeComponent::getSize() const {
		return Vector2(getWidth(), getHeight());
	}
	
	SizeComponentProxy::SizeComponentProxy(Entity *entity) : ComponentProxy(entity, NULL) {
		
	}
	
	void SizeComponentProxy::setSizeComponent(SizeComponent *sizeComponent) {
		component = sizeComponent;
		entity->addComponent(sizeComponent);
	}
	
	float SizeComponentProxy::getWidth() const {
		return reinterpret_cast<const SizeComponent *>(component)->getWidth();
	}
	float SizeComponentProxy::getHeight() const {
		return reinterpret_cast<const SizeComponent *>(component)->getHeight();
	}
	const Vector2 SizeComponentProxy::getSize() const {
		return reinterpret_cast<const SizeComponent *>(component)->getSize();
	}
}
