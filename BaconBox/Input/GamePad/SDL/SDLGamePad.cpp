#include "BaconBox/Input/GamePad/SDL/SDLGamePad.h"

#include <iostream>

#define BB_MIN_SDL_JOYSTICK_VALUE 32768.0f
#define BB_MAX_SDL_JOYSTICK_VALUE 32767.0f

namespace BaconBox {


	SDLGamePad::SDLGamePad(size_t index) : GamePad(index), joystick(NULL) {
		this->joystick = SDL_JoystickOpen(static_cast<int>(index));
		
		if (this->joystick) {
			int nbButtons = SDL_JoystickNumButtons(this->joystick);
			
			if (nbButtons < 0) {
				std::cout << "SDL_JoystickNumButtons returned " << nbButtons << ", the error message is:" << std::endl << SDL_GetError() << std::endl;
			}
			
			int nbAxes = SDL_JoystickNumAxes(this->joystick);
			
			if (nbAxes < 0) {
				std::cout << "SDL_JoystickNumAxes returned " << nbAxes << ", the error message is:" << std::endl << SDL_GetError() << std::endl;
			}
			
			if (nbButtons >= 0 && nbAxes >= 0) {
				state.init(nbButtons, nbAxes);
			}

			const char *temp_name = SDL_JoystickName(this->joystick);
			if (temp_name == NULL) {
				std::cout << "SDL_JoystickName returned NULL, the error message is:" << std::endl << SDL_GetError() << std::endl;
			}
			else {
				this->gamepad_name = temp_name;
			}
		} else {
			std::cout << "SDL_JoystickOpen for the game pad '" << index << "' returned NULL, the error message is:" << std::endl << SDL_GetError() << std::endl;
		}
	}

	SDLGamePad::~SDLGamePad() {
		if (this->joystick) {
			SDL_JoystickClose(this->joystick);
		}
	}

	void SDLGamePad::updateDevice() {
		GamePad::updateDevice();
		getPreviousButtons() = getButtons();
		getPreviousThumbstick() = getThumbstick();

		for (int i = 0; i < getButtons().size(); i++) {
			getButtons()[i] = SDL_JoystickGetButton(this->joystick, i);

			if (isButtonPressed(i)) {
				buttonPress(GamePadButtonSignalData(state, i, getIndex()));

			} else if (isButtonHeld(i)) {
				buttonHold(GamePadButtonSignalData(state, i, getIndex()));

			} else if (isButtonReleased(i)) {
				buttonRelease(GamePadButtonSignalData(state, i, getIndex()));
			}
		}

		for (std::vector<float>::size_type i = 0; i < getThumbstick().size(); ++i) {
			float  axisValue = SDL_JoystickGetAxis(this->joystick, static_cast<int>(i));
			float finalAxisValue;

			if (axisValue < 0) {
				finalAxisValue = axisValue / BB_MIN_SDL_JOYSTICK_VALUE;

			} else {
				finalAxisValue = axisValue / BB_MAX_SDL_JOYSTICK_VALUE;
			}

			getThumbstick()[i] =  finalAxisValue;

			if (getThumbstick()[i] != getPreviousThumbstick()[i]) {
				thumbstickMove(GamePadThumbstickSignalData(state, i, getIndex()));
			}
		}
	}
}
