/**
 * @file
 * @ingroup Input
 */
#ifndef BB_SDL_INPUT_MANAGER_H
#define BB_SDL_INPUT_MANAGER_H

#include "BaconBox/PlatformFlagger.h"


#include "BaconBox/Input/InputManager.h"

namespace BaconBox {
	class SDLInputManager : public InputManager {
		friend class InputManager;
		BB_SINGLETON_DECL(SDLInputManager);
	public:
		bool isRunning() const;
	protected:
		SDLInputManager();
		~SDLInputManager();
		void update();
	private:
		bool running;
	};
}

#endif
