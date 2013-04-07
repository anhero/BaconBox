#include "BaconBox/Input/GamePad/GamePadThumbstickSignalData.h"

using namespace BaconBox;

GamePadThumbstickSignalData::GamePadThumbstickSignalData(const GamePadState& newGamePadState,
														 size_t newThumbstickIndex, size_t gamePadIndex):
GamePadSignalData(newGamePadState, gamePadIndex), thumbstickIndex(newThumbstickIndex) {
}

GamePadThumbstickSignalData::~GamePadThumbstickSignalData() {
}
