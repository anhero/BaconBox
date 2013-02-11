#ifndef BB_FLASHENGINE_H
#define BB_FLASHENGINE_H

#include <AS3/AS3.h>
#include <AS3/AS3++.h>


#include "BaconBox/Core/BaseEngine.h"

namespace BaconBox {

	class FlashEngine : public BaseEngine {
		friend class Engine;
		friend class FlashEntityManager;
	public:

		State *addState(State *newState);
		void removeState(const std::string &name);
		static AS3::local::var getStage(); 
	private:
		FlashEngine();
		static AS3::local::var stage;
		AS3::local::var currentStateMovieClip;

		void swapActiveMovieClip(AS3::local::var newMovieClip);
	};
}

#endif
