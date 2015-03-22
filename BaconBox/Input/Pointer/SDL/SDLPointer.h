/**
 * @file
 * @ingroup Input
 */
#ifndef BB_SDL_POINTER_H
#define BB_SDL_POINTER_H

#include "BaconBox/Input/Pointer/Pointer.h"
#include <SDL2/SDL_touch.h>
#include <map>
#include <set>

namespace BaconBox {
	/**
	 * Pointer implementation for SDL.
	 * @ingroup Input
	 */
	class SDLPointer : public Pointer {
		friend class InputManager;
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
		 * Whether we have to handle a touch screen
		 */
		bool hasTouchscreen;

		/**
		 * Touchscreen specifics
		 * Returns true when touch events are happening.
		 */
		bool updateTouchScreen();

		/**
		 * List of SDL IDs in relationship of BaconBox pointers, for the last
		 * finger touches. Used to track fingers.
		 */
		std::map<SDL_FingerID, unsigned int> touchCache;

		/**
		 * List of available BaconBox pointer IDs
		 */
		std::set<unsigned int> availIDs;
	};
}

#endif
