#ifndef BB_PLAY_STATE_H
#define BB_PLAY_STATE_H

#include <Core/State.h>

namespace BaconBox {
	class PlayState : public State {
	public:
		PlayState(const std::string newName);
		
		void update();
		
		void render();
	};
}

#endif