#ifndef BB_COMPONENT_H
#define BB_COMPONENT_H

#include "ID.h"

namespace BaconBox {
	class Entity;
	
	class Component {
	public:
		HAS_ID(Component);
		
		void sendMessage(int message, void *data);
		virtual void receiveMessage(int id, int message, void *data);
	private:
		Entity *entity;
	};
}

#endif
