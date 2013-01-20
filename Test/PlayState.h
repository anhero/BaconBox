#ifndef __Test__PlayState__
#define __Test__PlayState__

#include <string>

#include <BaconBox/Core/State.h>

namespace BaconBox {
	class PlayState : public State {
	public:
		PlayState(const std::string &newName = "PlayState");
	private:
	};
}

#endif /* defined(__Test__PlayState__) */
