/**
 * @file
 */
#ifndef BB_GAMEPAD_H
#define BB_GAMEPAD_H

#include "BaconBox/Input/GamePad/GamePad.h"
#include <SDL2/SDL.h>

namespace BaconBox {
	/**
	 * 
	 */
	class SDLGamePad : GamePad {
        friend class InputManager;
	protected:
		SDLGamePad(size_t index);
		
		/**
		 * Destructor.
		 */
		~SDLGamePad();
		
		/**
		 * Abstract update method. This will be called to update the device's
		 * state.
		 */
		void updateDevice();
        
    private:
        SDL_Joystick *joystick;
	};
}

#endif // BB_GAMEPAD_H





