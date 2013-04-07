#include "BaconBox/Input/GamePad/SDL/SDLGamePad.h"

#define BB_MIN_SDL_JOYSTICK_VALUE 32768.0f
#define BB_MAX_SDL_JOYSTICK_VALUE 32767.0f

namespace BaconBox {


	SDLGamePad::SDLGamePad(size_t index) : GamePad(index) {
		joystick = SDL_JoystickOpen(static_cast<int>(index));
		state.init(SDL_JoystickNumButtons(joystick), SDL_JoystickNumAxes(joystick));

	}

	SDLGamePad::~SDLGamePad() {
		SDL_JoystickClose(joystick);
	}

	void SDLGamePad::updateDevice() {
		GamePad::updateDevice();
		getPreviousButtons() = getButtons();
		getPreviousThumbstick() = getThumbstick();

		for (int i = 0; i < getButtons().size(); i++) {
			getButtons()[i] = SDL_JoystickGetButton(joystick, i);

			if (isButtonPressed(i)) {
				buttonPress(GamePadButtonSignalData(state, i, getIndex()));

			} else if (isButtonHeld(i)) {
				buttonHold(GamePadButtonSignalData(state, i, getIndex()));

			} else if (isButtonReleased(i)) {
				buttonRelease(GamePadButtonSignalData(state, i, getIndex()));
			}
		}

		for (std::vector<float>::size_type i = 0; i < getThumbstick().size(); ++i) {
			float  axisValue = SDL_JoystickGetAxis(joystick, static_cast<int>(i));
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
