#ifndef BB_FLASHENGINE_H
#define BB_FLASHENGINE_H

#include <AS3/AS3.h>
#include <AS3/AS3++.h>


#include "BaconBox/Core/BaseEngine.h"

namespace BaconBox {

	class FlashEngine : public BaseEngine {
		friend class Engine;
	public:

		State *addState(State *newState);
		void removeState(const std::string &name);
	private:
		FlashEngine();
		AS3::local::var stage;
	};
}

#endif
