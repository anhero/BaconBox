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

	AS3_GetVarxxFromVar(eventType, MouseEvent.MOUSE_UP);
	args[0] = eventType;
	mouseUpFun = args[1] = AS3::local::internal::new_Function(mouseUpEventListener, reinterpret_cast<void*>(this));;
	FlashHelper::callMethod(stage, "addEventListener", 2, args);

	AS3_GetVarxxFromVar(eventType, MouseEvent.MOUSE_DOWN);
	args[0] = eventType;
	mouseDownFun = args[1] = AS3::local::internal::new_Function(mouseUpEventListener, reinterpret_cast<void*>(this));;
	FlashHelper::callMethod(stage, "addEventListener", 2, args);

	AS3_GetVarxxFromVar(eventType, MouseEvent.MOUSE_MOVE);
	args[0] = eventType;
	mouseMoveFun = args[1] = AS3::local::internal::new_Function(mouseUpEventListener, reinterpret_cast<void*>(this));
	FlashHelper::callMethod(stage, "addEventListener", 2, args);


}




FlashPointer::~FlashPointer() {
	inline_as3("import flash.events.MouseEvent; \n");

	AS3::local::var stage = FlashEngine::getStage();
	AS3::local::var eventType;
	AS3::local::var args[2];

	AS3_GetVarxxFromVar(eventType, MouseEvent.MOUSE_UP);
	args[0] = eventType;
	args[1] = mouseDownFun;
	FlashHelper::callMethod(stage, "removeEventListener", 2, args);

	AS3_GetVarxxFromVar(eventType, MouseEvent.MOUSE_DOWN);
	args[0] = eventType;
	args[1] = mouseDownFun;
	FlashHelper::callMethod(stage, "removeEventListener", 2, args);

	AS3_GetVarxxFromVar(eventType, MouseEvent.MOUSE_MOVE);
	args[0] = eventType;
	args[1] = mouseMoveFun;
	FlashHelper::callMethod(stage, "removeEventListener", 2, args);
}


void FlashPointer::pointerUpCallBack(AS3::local::var event){
	int x = AS3::local::internal::int_valueOf(FlashHelper::getProperty(event, "stageX"));
	int y = AS3::local::internal::int_valueOf(FlashHelper::getProperty(event, "stageY"));
	mouseState.pos = Vector2(static_cast<float>(x), static_cast<float>(y));
	mouseState.leftButton = AS3::local::internal::bool_valueOf(FlashHelper::getProperty(event, "buttonDown"));
}

AS3::local::var FlashPointer::mouseUpEventListener(void *arg, AS3::local::var as3Args){
	reinterpret_cast<FlashPointer*>(arg)->pointerUpCallBack(FlashHelper::callMethod(as3Args, "pop", 0, NULL));
	return AS3::local::internal::_null;
}

void FlashPointer::pointerDownCallBack(AS3::local::var event){
	getCursorPreviousButtons(0) = getCursorButtons(0);
	getCursorPreviousPosition(0) = getCursorPosition(0);

	int x = AS3::local::internal::int_valueOf(FlashHelper::getProperty(event, "stageX"));
	int y = AS3::local::internal::int_valueOf(FlashHelper::getProperty(event, "stageY"));
	getCursorPosition(0) = Vector2(static_cast<float>(x), static_cast<float>(y));
	getCursorButtons(0)[CursorButton::LEFT] = true;
}

AS3::local::var FlashPointer::mouseDownEventListener(void *arg, AS3::local::var as3Args){
	reinterpret_cast<FlashPointer*>(arg)->pointerDownCallBack(FlashHelper::callMethod(as3Args, "pop", 0, NULL));
	return AS3::local::internal::_null;
}

void FlashPointer::pointerMoveCallBack(AS3::local::var event){
	getCursorPreviousButtons(0) = getCursorButtons(0);
	getCursorPreviousPosition(0) = getCursorPosition(0);

	int x = AS3::local::internal::int_valueOf(FlashHelper::getProperty(event, "stageX"));
	int y = AS3::local::internal::int_valueOf(FlashHelper::getProperty(event, "stageY"));
	getCursorPosition(0) = Vector2(static_cast<float>(x), static_cast<float>(y));
}

AS3::local::var FlashPointer::mouseMoveEventListener(void *arg, AS3::local::var as3Args){
	reinterpret_cast<FlashPointer*>(arg)->pointerMoveCallBack(FlashHelper::callMethod(as3Args, "pop", 0, NULL));
	return AS3::local::internal::_null;
}

void FlashPointer::updateDevice() {
	getCursorPreviousButtons(0) = getCursorButtons(0);
	getCursorPreviousPosition(0) = getCursorPosition(0);

	getCursorButtons(0)[CursorButton::LEFT] = mouseState.leftButton;
	getCursorPosition(0) = mouseState.pos;

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
