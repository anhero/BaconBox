#include "Visibility.h"

#include "BaconBox/Core/IDManager.h"
#include "BaconBox/Helper/ValueChangedData.h"
#include "BaconBox/Core/Entity.h"

namespace BaconBox {
	int Visibility::MESSAGE_IS_VISIBLE = IDManager::generateID();
	int Visibility::MESSAGE_SET_VISIBLE = IDManager::generateID();
	int Visibility::MESSAGE_VISIBILITY_CHANGED = IDManager::generateID();
	
	Visibility::Visibility() : Component(), visible(true) {
	}
	
	Visibility::Visibility(const Visibility &src) : Component(src), visible(src.visible) {
	}
	
	Visibility::~Visibility() {
	}
	
	Visibility &Visibility::operator=(const Visibility &src) {
		if (this != &src) {
			this->setVisible(src.visible);
		}
		
		return *this;
	}
	
	Visibility *Visibility::clone() const {
		return new Visibility(*this);
	}

	void Visibility::receiveMessage(int senderID, int destID, int message, void *data) {
		if (destID == Visibility::ID) {
			if (message == MESSAGE_IS_VISIBLE) {
				*reinterpret_cast<bool *>(data) = this->isVisible();
			} else if (message == MESSAGE_SET_VISIBLE) {
				this->setVisible(*reinterpret_cast<bool *>(data));
			}
		}
	}
	
	bool Visibility::isVisible() const {
		return this->visible;
	}
	
	void Visibility::setVisible(bool newVisible) {
		if (newVisible != this->visible) {
			ValueChangedData<bool> data(this->visible, newVisible);
			this->visible = newVisible;
			this->sendMessage(Entity::BROADCAST, MESSAGE_VISIBILITY_CHANGED, &(data));
		}
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
