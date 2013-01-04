/**
 * @file
 * @ingroup Input
 */
#ifndef BB_SDL_INPUT_MANAGER_H
#define BB_SDL_INPUT_MANAGER_H

#include "BaconBox/PlatformFlagger.h"

#ifdef BB_SDL

#include "BaconBox/Input/InputManager.h"

namespace BaconBox {
	class SDLInputManager : public InputManager {
		friend class InputManager;
	public:
		static SDLInputManager* getSDLInstance();
		bool isRunning() const;
	protected:
		SDLInputManager();
		~SDLInputManager();
		void update();
	private:
		static SDLInputManager* sdlInstance;
		bool running;
	};
}

#endif
#endif
