#ifndef BB_COMPONENT_H
#define BB_COMPONENT_H

#include "ID.h"

namespace BaconBox {
	class Component {
	public:
		virtual int getId() const;
	};
}

#endif
