#include "BaconBox/Input/GamePad/GamePadState.h"
using namespace BaconBox;

GamePadState::GamePadState() : InputState() {
}

GamePadState::~GamePadState() {
}

float GamePadState::getButton(size_t buttonIndex) const {
	if (buttonIndex >= buttons.size()) {
		if (buttons.empty()) {
			buttonIndex = 0u;

		} else {
			buttonIndex = buttons.size() - 1;
		}
	}

	return buttons[buttonIndex];
}

float GamePadState::getPreviousButton(size_t buttonIndex) const {
	if (buttonIndex >= previousButtons.size()) {
		if (previousButtons.empty()) {
			buttonIndex = 0u;

		} else {
			buttonIndex = previousButtons.size() - 1;
		}
	}

	return previousButtons[buttonIndex];
}


void GamePadState::init(size_t nbOfButtons, size_t nbOfThumbstick) {
	buttons = std::vector<float>(nbOfButtons, 0.0f);
	previousButtons = std::vector<float>(nbOfButtons, 0.0f);
	thumbsticks = std::vector<float>(nbOfThumbstick, 0.0f);
	previousThumbsticks = std::vector<float>(nbOfThumbstick, 0.0f);
}

const float GamePadState::getThumbstick(size_t thumbstickIndex) const {
	if (thumbstickIndex >= thumbsticks.size()) {
		if (thumbsticks.empty()) {
			thumbstickIndex = 0u;

		} else {
			thumbstickIndex = thumbsticks.size() - 1;
		}
	}

	return thumbsticks[thumbstickIndex];
}




bool GamePadState::isButtonPressed(size_t buttonIndex) const {
	return (buttons[buttonIndex] && !previousButtons[buttonIndex]);
}

bool GamePadState::isButtonHeld(size_t buttonIndex) const {
	return (buttons[buttonIndex] && previousButtons[buttonIndex]);
}

bool GamePadState::isButtonReleased(size_t buttonIndex) const {
	return (!buttons[buttonIndex] && previousButtons[buttonIndex]);
}
