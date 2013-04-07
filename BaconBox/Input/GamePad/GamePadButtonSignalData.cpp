#include "BaconBox/Input/GamePad/GamePadButtonSignalData.h"

using namespace BaconBox;

GamePadButtonSignalData::GamePadButtonSignalData(const GamePadState& newGamePadState,
												 size_t newButtonIndex, size_t gamePadIndex):
GamePadSignalData(newGamePadState, gamePadIndex), buttonIndex(newButtonIndex) {
}

GamePadButtonSignalData::~GamePadButtonSignalData() {
}
