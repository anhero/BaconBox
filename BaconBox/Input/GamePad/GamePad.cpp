#include "BaconBox/Input/GamePad/GamePad.h"

#include "BaconBox/Input/InputManager.h"

using namespace BaconBox;

GamePad *GamePad::getDefault() {
	return InputManager::getDefaultGamePad();
}

const GamePadState &GamePad::getState() const {
	return state;
}

GamePad::GamePad(size_t index) : InputDevice() {
	gamePadIndex = index;
}

GamePad::~GamePad() {
}

void GamePad::updateDevice() {
	InputDevice::updateDevice();
}


size_t GamePad::getIndex() {
	return gamePadIndex;
}



std::vector<float> &GamePad::getPreviousButtons() {
	return state.previousButtons;
}

std::vector<float> &GamePad::getButtons() {
	return state.buttons;
}

std::vector<float> &GamePad::getThumbstick() {
	return state.thumbsticks;
}

std::vector<float> &GamePad::getPreviousThumbstick() {
	return state.previousThumbsticks;
}



bool GamePad::isButtonPressed(unsigned int buttonIndex) const {
	return state.isButtonPressed(buttonIndex);
}

bool GamePad::isButtonHeld(unsigned int buttonIndex) const {
	return state.isButtonHeld(buttonIndex);
}

bool GamePad::isButtonReleased(unsigned int buttonIndex) const {
	return state.isButtonReleased(buttonIndex);
}

size_t GamePad::getNbOfButton() {
	return getButtons().size();
}

size_t GamePad::getNbOfThumbstick() {
	return getThumbstick().size();
}

const std::string GamePad::getName() const {
	return this->gamepad_name;
}
