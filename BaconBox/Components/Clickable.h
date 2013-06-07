#ifndef BB_CLICKABLE_H
#define BB_CLICKABLE_H


#include "BaconBox/Core/Component.h"
#include "sigly.h"
namespace BaconBox {
	class Clickable : public Component {
	public:
		BB_ID_HEADER;
		
		Clickable();
				
		virtual ~Clickable();
		sigly::Signal0<> moveOver;
		sigly::Signal0<> moveOut;
		sigly::Signal0<> pressed;
		sigly::Signal0<> released;
		
		virtual void receiveMessage(int senderID, int destID, int message, void *data);
		

	private:
	

	};
	
	class ClickableProxy : public ComponentProxy {
	public:
		ClickableProxy(Entity *entity, bool mustAddComponent = true);
		
		sigly::Signal0<> * moveOver;
		sigly::Signal0<> * moveOut;
		sigly::Signal0<> * pressed;
		sigly::Signal0<> * released;
				
	protected:
	};

}

#endif
