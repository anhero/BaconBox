#include "BaconBox/PlatformFlagger.h"

#include "BaconBox/Input/SDL/SDLInputManager.h"

#include "BaconBox/Core/Engine.h"

#include <SDL2/SDL.h>

using namespace BaconBox;

BB_SINGLETON_IMPL(SDLInputManager)

bool SDLInputManager::isRunning() const {
	return running;
}

SDLInputManager::SDLInputManager() : InputManager(), running(true) {
}

SDLInputManager::~SDLInputManager() {
}

void SDLInputManager::update() {
	SDL_Event event;
	// We need to fish all the events otherwise we are getting "lag" from an
	// event queue that fills up more quickly than we handle.
	while (SDL_PollEvent(&event)) {
		switch(event.type) {
			case SDL_QUIT:
				running = false;
				break;
			default:
				break;
		}
	}
	InputManager::update();
}

