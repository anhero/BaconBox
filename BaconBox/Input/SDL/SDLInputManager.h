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
	public:
		/**
		 * Gets the singleton instance.
		 * @return Pointer to the instance.
		 */
		static SDLInputManager &getInstance();
		void destroyInstance();

		bool isRunning() const;
	protected:
		SDLInputManager();
		~SDLInputManager();
		void update();
		static SDLInputManager * instance;
	private:
		bool running;
	};
}

#endif
