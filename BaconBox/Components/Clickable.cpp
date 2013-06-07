#include "BaconBox/Components/Clickable.h"

namespace BaconBox {
	BB_ID_IMPL(Clickable);

	Clickable::Clickable() : Component() {
		
	}
	
	Clickable::~Clickable() {
		
	}
	
	void Clickable::receiveMessage(int senderID, int destID, int message, void *data) {
		Component::receiveMessage(senderID, destID, message, data);
	}
	
	
	
	ClickableProxy::ClickableProxy(Entity* entity, bool mustAddComponent): BB_PROXY_CONSTRUCTOR(new Clickable())  {
		moveOver = &reinterpret_cast<Clickable*>(component)->moveOver;
		moveOut = &reinterpret_cast<Clickable*>(component)->moveOut;
		pressed = &reinterpret_cast<Clickable*>(component)->pressed;
		released = &reinterpret_cast<Clickable*>(component)->released;
	}


}
