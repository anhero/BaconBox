#include "BaconBox/Input/Pointer/PointerState.h"

#include "BaconBox/Input/Pointer/CursorButton.h"

#include "BaconBox/Console.h"
#include "BaconBox/Display/Window/MainWindow.h"
using namespace BaconBox;

const size_t PointerState::DEFAULT_NB_CURSORS = 1;

PointerState::PointerState(size_t nbCursors):
	InputState(), cursors(std::vector<CursorState>(nbCursors, CursorState())) {
}

PointerState::~PointerState() {
}

const CursorState &PointerState::getCursorState(size_t index) const {
	// If we go out of bound, we write an error message and we return the last
	// cursor state.
	if (index >= cursors.size()) {
		if (cursors.empty()) {
			index = 0u;

		} else {
			index = cursors.size() - 1;
		}

		Console::println("Tried to get a cursor's state that does not exist, returning instead the cursor state with the highest index.");
	}

	return cursors[index];
}

const Vector2 &PointerState::getCursorPosition(size_t index) {
	return cursors[index].position;
}

void PointerState::setCursorPosition(unsigned int index, Vector2 pos) {
	
	float windowOrientationAngleOffset = 0.0f;
	Vector2 windowOrientationOffset;
	switch (MainWindow::getInstance().getOrientation()) {
		case WindowOrientation::HORIZONTAL_LEFT:
			windowOrientationAngleOffset = -90.0f;
			windowOrientationOffset.x = static_cast<float>(MainWindow::getInstance().getRealContextHeight());
			break;
			
		case WindowOrientation::HORIZONTAL_RIGHT:
			windowOrientationAngleOffset = 90.0f;
			windowOrientationOffset.y = static_cast<float>(MainWindow::getInstance().getRealContextWidth());
			break;
		default:
			break;
	}
	
	pos.rotate(windowOrientationAngleOffset);
	pos +=(windowOrientationOffset);
	cursors[index].position = pos;
}


Vector2 &PointerState::getCursorPreviousPosition(size_t index) {
	return cursors[index].previousPosition;
}

std::vector<bool> &PointerState::getCursorButtons(size_t index) {
	return cursors[index].buttons;
}

std::vector<bool> &PointerState::getCursorPreviousButtons(size_t index) {
	return cursors[index].previousButtons;
}
