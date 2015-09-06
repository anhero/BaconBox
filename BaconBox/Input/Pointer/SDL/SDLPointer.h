/**
 * @file
 * @ingroup Input
 */
#ifndef BB_SDL_POINTER_H
#define BB_SDL_POINTER_H

#include <map>
#include <set>
#include <SDL2/SDL.h>
#include "BaconBox/Input/Pointer/Pointer.h"
#include "BaconBox/Input/SDL/SDLInputManager.h"

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
