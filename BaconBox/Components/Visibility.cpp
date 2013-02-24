#include "Visibility.h"

namespace BaconBox {
	Visibility::Visibility() : Component(), visible(true) {
	}
	
	Visibility::Visibility(const Visibility &src) : Component(src), visible(src.visible) {
	}
	
	Visibility::~Visibility() {
	}
	
	Visibility &Visibility::operator=(const Visibility &src) {
		if (this != &src) {
		}
		
		return *this;
	}
	
	Visibility *Visibility::clone() const {
		return new Visibility(*this);
	}
	
	bool Visibility::isVisible() const {
		return this->visible;
	}
	
	void Visibility::setVisible(bool newVisible) {
		this->visible = newVisible;
	}
	
	VisibilityProxy::VisibilityProxy(Entity* entity, bool mustAddComponent): BB_PROXY_CONSTRUCTOR(new Visibility())  {
	}
	
	
	bool VisibilityProxy::isVisible() const {
	    return reinterpret_cast<Visibility*>(this->component)->isVisible();
	}
	
	void VisibilityProxy::setVisible(bool newVisible) {
		reinterpret_cast<Visibility*>(this->component)->setVisible(newVisible);
	}
}
