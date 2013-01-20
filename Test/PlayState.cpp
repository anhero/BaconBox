#include "PlayState.h"

#include <BaconBox/MovieClipEntity/MovieClipEntity.h>
#include <BaconBox/Components/Transform.h>

namespace BaconBox {
	PlayState::PlayState(const std::string &newName) : State(newName) {
		MovieClipEntity *e = new MovieClipEntity();
		this->add(e);
	}
}