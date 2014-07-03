#include "BaconBox/Input/Pointer/Flash/FlashPointer.h"
#include "BaconBox/Core/Flash/FlashEngine.h"
#include "BaconBox/Console.h"
#include "BaconBox/Helper/Flash/FlashHelper.h"

using namespace BaconBox;

FlashPointer::FlashPointer() : Pointer() {
	 inline_as3("import flash.events.MouseEvent; \n");

	AS3::local::var stage = FlashEngine::getStage();
	AS3::local::var eventType;
	AS3::local::var args[2];

	mouseFun = args[1] = AS3::local::internal::new_Function(mouseEventListener, reinterpret_cast<void*>(this));


	AS3_GetVarxxFromVar(args[0], MouseEvent.MOUSE_UP);
	FlashHelper::callMethod(stage, "addEventListener", 2, args);

	AS3_GetVarxxFromVar(args[0], MouseEvent.MOUSE_DOWN);
	FlashHelper::callMethod(stage, "addEventListener", 2, args);

	AS3_GetVarxxFromVar(args[0], MouseEvent.MOUSE_MOVE);
	FlashHelper::callMethod(stage, "addEventListener", 2, args);

}




FlashPointer::~FlashPointer() {
	inline_as3("import flash.events.MouseEvent; \n");

	AS3::local::var stage = FlashEngine::getStage();
	AS3::local::var eventType;
	AS3::local::var args[2];

	args[1] = mouseFun;

	AS3_GetVarxxFromVar(args[0], MouseEvent.MOUSE_UP);
	FlashHelper::callMethod(stage, "removeEventListener", 2, args);

	AS3_GetVarxxFromVar(args[0], MouseEvent.MOUSE_DOWN);
	FlashHelper::callMethod(stage, "removeEventListener", 2, args);

	AS3_GetVarxxFromVar(args[0], MouseEvent.MOUSE_MOVE);
	FlashHelper::callMethod(stage, "removeEventListener", 2, args);
}


 AS3::local::var FlashPointer::mouseEventListener(void *arg, AS3::local::var as3Args){
	AS3::local::var event = FlashHelper::callMethod(as3Args, "pop", 0, NULL);
	int x = AS3::local::internal::int_valueOf(FlashHelper::getProperty(event, "stageX"));
	int y = AS3::local::internal::int_valueOf(FlashHelper::getProperty(event, "stageY"));
	reinterpret_cast<FlashPointer*>(arg)->mouseState.pos = Vector2(static_cast<float>(x), static_cast<float>(y));
	reinterpret_cast<FlashPointer*>(arg)->mouseState.leftButton = AS3::local::internal::bool_valueOf(FlashHelper::getProperty(event, "buttonDown"));
	return AS3::local::internal::_null;
}

void FlashPointer::updateDevice() {
	getCursorPreviousButtons(0) = getCursorButtons(0);
	getCursorPreviousPosition(0) = getCursorPosition(0);

	getCursorButtons(0)[CursorButton::LEFT] = mouseState.leftButton;
	setCursorPosition(0, mouseState.pos);

		if(isButtonPressed(0)) {
			buttonPress(PointerButtonSignalData(state, 0, 0));
		} else if(isButtonHeld(0)) {
			buttonHold(PointerButtonSignalData(state, 0, 0));
		} else if(isButtonReleased(0)) {
			buttonRelease(PointerButtonSignalData(state, 0, 0));
		}
		

	// We check the pointer's position.
	if(hasMoved()) {
		Pointer::move.shoot(PointerSignalData(state, 0));
	}
}
