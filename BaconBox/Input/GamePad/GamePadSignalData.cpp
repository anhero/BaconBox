#include "BaconBox/Input/GamePad/GamePadSignalData.h"

using namespace BaconBox;

GamePadSignalData::GamePadSignalData(const GamePadState& newGamePadState, size_t gamePadIndex):
InputSignalData(), gamePadState(newGamePadState), gamePadIndex(gamePadIndex) {
}

GamePadSignalData::~GamePadSignalData() {
}
