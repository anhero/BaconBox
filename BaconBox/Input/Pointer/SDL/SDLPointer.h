/**
 * @file
 * @ingroup Input
 */
#ifndef BB_SDL_POINTER_H
#define BB_SDL_POINTER_H

#include "BaconBox/Input/Pointer/Pointer.h"
#include "BaconBox/Input/SDL/SDLInputManager.h"
#include <SDL2/SDL.h>

namespace BaconBox {
	/**
	 * Pointer implementation for SDL.
	 * @ingroup Input
	 */
	class SDLPointer : public Pointer {
		friend class InputManager;
		friend class SDLInputManager;
	public:
		virtual int getWheelScroll() const;
	protected:
		/**
		 * Default constructor.
		 */
		SDLPointer();
		
		/**
		 * Destructor.
		 */
		~SDLPointer();
		
		/**
		 * Updates the mouse's buttons state from SDL's mouse state.
		 */
		void updateDevice();

		/**
		 * Notifies the Pointer that a wheel event happened.
		 * The device is not yet updated.
		 */
		void handleWheel(SDL_Event event);

		/**
		 * Wheel scroll delta
		 */
		int wheelScroll;
		/**
		 * Used to access the wheel scroll delta post-event processing.
		 */
		int lastWheelScroll;
	};
}

#endif
