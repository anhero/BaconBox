#ifndef BB_COMPONENT_H
#define BB_COMPONENT_H

#include "ID.h"

namespace BaconBox {
	class Entity;
	
	class Component {
	public:
		HAS_ID(Component);
	private:
		Entity *entity;
	};
}

#endif
