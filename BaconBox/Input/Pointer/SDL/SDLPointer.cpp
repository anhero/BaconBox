#include "BaconBox/Input/Pointer/SDL/SDLPointer.h"
#include "BaconBox/Console.h"

#include <stdint.h>

#include <SDL2/SDL.h>

using namespace BaconBox;

// FIXME : Properly resize in-situ? Geting max pointers seems impossible from SDL.
#define ASSUME_SDL_MAX_POINTERS 10

SDLPointer::SDLPointer() : Pointer(ASSUME_SDL_MAX_POINTERS) {
	hasTouchscreen = (SDL_GetNumTouchDevices() > 0);
	if (hasTouchscreen) {
		for (unsigned int i=0; i<=ASSUME_SDL_MAX_POINTERS; i++) {
			availIDs.insert(i);
		}
	}
}

SDLPointer::~SDLPointer() {
}

void SDLPointer::updateDevice() {
	getCursorPreviousButtons(0) = getCursorButtons(0);
	getCursorPreviousPosition(0) = getCursorPosition(0);
	int x, y; // For the mouse position.
	// We check the pointer's buttons' states.
	Uint8 buttons = SDL_GetMouseState(&x, &y);
	Vector2 pos(static_cast<float>(x), static_cast<float>(y));
	setCursorPosition(0, pos);
	getCursorButtons(0)[CursorButton::LEFT] = static_cast<bool>(buttons & SDL_BUTTON(SDL_BUTTON_LEFT));
	getCursorButtons(0)[CursorButton::RIGHT] = static_cast<bool>(buttons & SDL_BUTTON(SDL_BUTTON_RIGHT));
	getCursorButtons(0)[CursorButton::MIDDLE] = static_cast<bool>(buttons & SDL_BUTTON(SDL_BUTTON_MIDDLE));
	getCursorButtons(0)[CursorButton::OTHER_BUTTON_1] = static_cast<bool>(buttons & SDL_BUTTON(SDL_BUTTON_X1));
	getCursorButtons(0)[CursorButton::OTHER_BUTTON_2] = static_cast<bool>(buttons & SDL_BUTTON(SDL_BUTTON_X2));
	//getCursorButtons(0)[CursorButton::SCROLL_UP] = static_cast<bool>(buttons & SDL_BUTTON(SDL_BUTTON_WHEELUP));
	//getCursorButtons(0)[CursorButton::SCROLL_DOWN] = static_cast<bool>(buttons & SDL_BUTTON(SDL_BUTTON_WHEELDOWN));
	for(CursorButton::Enum i = 0; i < CursorButton::NB_BUTTONS; ++i) {
		if(isButtonPressed(i)) {
			buttonPress(PointerButtonSignalData(state, 0, i));
		} else if(isButtonHeld(i)) {
			buttonHold(PointerButtonSignalData(state, 0, i));
		} else if(isButtonReleased(i)) {
			buttonRelease(PointerButtonSignalData(state, 0, i));
		}
	}

	// We check the pointer's position.
	if(hasMoved()) {
		Pointer::move.shoot(PointerSignalData(state, 0));
	}

	// Touch screen event handling
	if (hasTouchscreen) {
		updateTouchScreen();
	}
}

void SDLPointer::updateTouchScreen() {
	// Wrongly, but ususally rightly, assume one touchscreen
	SDL_TouchID touchscreenID = SDL_GetTouchDevice(0);
	if (!touchscreenID) {
		Console__error(SDL_GetError());
		return;
	}

	// Check the number of fingers currently active.
	// Used to track if a new finger is pressed or an old finger is released.
	int num_active_touches = SDL_GetNumTouchFingers(touchscreenID);

	// Build the set of current touches.
	// Used to determine what's new and what's gone.
	std::set<SDL_FingerID> currTouches;
	for (int i = 0; i < num_active_touches; i++) {
		currTouches.insert(SDL_GetTouchFinger(touchscreenID, i)->id);
	}

	// Map of removed touches
	std::map<SDL_FingerID, unsigned int> removedTouches;
	for (std::map<SDL_FingerID, unsigned int>::iterator it=touchCache.begin();
		 it!=touchCache.end(); ++it) {
		if (!currTouches.count(it->first)) {
			removedTouches.insert(
				std::pair<SDL_FingerID, unsigned int>(
					it->first,it->second));
		}
	}
	// Map of added touches
	std::map<SDL_FingerID, unsigned int> addedTouches;
	for (std::set<SDL_FingerID>::iterator it=currTouches.begin();
		 it!=currTouches.end(); ++it) {
		if (availIDs.size() > 0) {
			if (!touchCache.count(*it)) {
				unsigned int id = *(availIDs.begin());
				availIDs.erase(id);
				addedTouches.insert(std::pair<SDL_FingerID, unsigned int>(
					(*it), id
				));
			}
		}
#ifdef BB_DEBUG
		else {
			Console__print("No pointer IDs left to assign for finger.");
		}
#endif
	}

	// Remove old touches and recycle the available IDs AFTER handling.
	for (std::map<SDL_FingerID, unsigned int>::iterator it=removedTouches.begin();
		 it!=removedTouches.end(); ++it) {
		availIDs.insert(it->second);
		// Erase old touches from our map
		touchCache.erase(it->first);
	}

	// Save the new touches
	touchCache.insert(addedTouches.begin(), addedTouches.end());

	// Track the last states
	for (unsigned int i = 0;  i < ASSUME_SDL_MAX_POINTERS; i++) {
		getCursorPreviousPosition(i) = getCursorPosition(i);
		getCursorPreviousButtons(i)[CursorButton::LEFT] = getCursorButtons(i)[CursorButton::LEFT];
	}

	// Update the button presses
	for (std::map<SDL_FingerID, unsigned int>::iterator it=removedTouches.begin();
		 it!=removedTouches.end(); ++it) {
		getCursorButtons(it->second)[CursorButton::LEFT] = false;
	}
	for (std::map<SDL_FingerID, unsigned int>::iterator it=addedTouches.begin();
		 it!=addedTouches.end(); ++it) {
		getCursorButtons(it->second)[CursorButton::LEFT] = true;
	}
	// Update the cursor positions with all touches
	for (std::map<SDL_FingerID, unsigned int>::iterator it=touchCache.begin();
		 it!=touchCache.end(); ++it) {
			int x,y = 0;
			Vector2 pos = Vector2(x, y);
			setCursorPosition(it->second, pos);
	}

	// Do the signal sending dance!
	for (unsigned int i = 0;  i < ASSUME_SDL_MAX_POINTERS; i++) {
		if (isButtonPressed(CursorButton::LEFT, i)) {
			buttonPress(PointerButtonSignalData(state, i, CursorButton::LEFT));
		}
		else if (isButtonHeld(CursorButton::LEFT, i)) {
			buttonHold(PointerButtonSignalData(state, i, CursorButton::LEFT));
		}
		else if (isButtonReleased(CursorButton::LEFT, i)) {
			buttonRelease(PointerButtonSignalData(state, i, CursorButton::LEFT));
		}
		if (hasMoved(i)) {
			Pointer::move.shoot(PointerSignalData(state, i));
		}
	}


}
