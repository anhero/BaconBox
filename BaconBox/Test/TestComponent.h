#ifndef BB_TEST_COMPONENT_H
#define BB_TEST_COMPONENT_H

#include "Component.h"

namespace BaconBox {
	class TestComponent : public Component {
	public:
		virtual int getId() const;
		
		int x;
	};
}

#endif