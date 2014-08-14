#include "BaconBox/Input/Pointer/Android/AndroidPointer.h"
#include "BaconBox/Input/Pointer/CursorButton.h"
#include "BaconBox/Display/Window/MainWindow.h"

#include "BaconBox/Console.h"
#include "BaconBox/Display/Window/Android/android_native_app_glue.h"
#include <android/input.h>

namespace BaconBox {
	#define ANDROID_MAX_POINTERS 10

	AndroidPointer::AndroidPointer(): Pointer(ANDROID_MAX_POINTERS), touchPos(ANDROID_MAX_POINTERS), touchPressed(ANDROID_MAX_POINTERS) {
		PRLN("AndroidPointer::AndroidPointer(): !!");
        for(int i = 0; i < ANDROID_MAX_POINTERS; i++){
        	touchPressed[i] = false;
        }
	}

	AndroidPointer::~AndroidPointer() {
	}

	void AndroidPointer::updateDevice() {
		for (unsigned int i = 0;  i < ANDROID_MAX_POINTERS; i++) {
			getCursorPreviousPosition(i) = getCursorPosition(i);
			setCursorPosition(i, this->touchPos[i]);
			getCursorPreviousButtons(i)[CursorButton::LEFT] = getCursorButtons(i)[CursorButton::LEFT];
			getCursorButtons(i)[CursorButton::LEFT] = this->touchPressed[i];

			if (isButtonPressed(CursorButton::LEFT, i)) {
				buttonPress(PointerButtonSignalData(state, i, CursorButton::LEFT));

			} else if (isButtonHeld(CursorButton::LEFT, i)) {
				buttonHold(PointerButtonSignalData(state, i, CursorButton::LEFT));

			} else if (isButtonReleased(CursorButton::LEFT, i)) {
				buttonRelease(PointerButtonSignalData(state, i, CursorButton::LEFT));
			}

			if (hasMoved(i)) {
				Pointer::move.shoot(PointerSignalData(state, i));
			}
		}


	}

	void AndroidPointer::receiveInput(struct android_app* app, AInputEvent* event){
		int nbTouch = AMotionEvent_getPointerCount(event);
		if(nbTouch > ANDROID_MAX_POINTERS) nbTouch = ANDROID_MAX_POINTERS;
        for(int i = 0; i < nbTouch; i++){
	        touchPos[i].x = AMotionEvent_getX(event, i);// / MainWindow::getInstance().getResolutionWidth() * MainWindow::getInstance().getContextWidth();
	        touchPos[i].y = AMotionEvent_getY(event, i);// / MainWindow::getInstance().getResolutionHeight() * MainWindow::getInstance().getContextHeight();
	    }

        	int32_t compositedAction = AMotionEvent_getAction(event);
        	size_t pointerIndex = (compositedAction & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK)
            >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;
            size_t pointerId = AMotionEvent_getPointerId(event, pointerIndex);
            size_t action = compositedAction  & AMOTION_EVENT_ACTION_MASK;
            
	        // if (action == AMOTION_EVENT_ACTION_POINTER_DOWN || action == AMOTION_EVENT_ACTION_POINTER_UP) {
	        //  	pointerIndex = (compositedAction & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK) >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;
         //        pointerId = AMotionEvent_getPointerId(event, pointerIndex);
	        // }

	        if (action == AMOTION_EVENT_ACTION_DOWN || action == AMOTION_EVENT_ACTION_POINTER_DOWN){
	        	touchPressed[pointerId] = true;

	        }
	        else if(action == AMOTION_EVENT_ACTION_UP || action == AMOTION_EVENT_ACTION_POINTER_UP){ 
	        	touchPressed[pointerId] = false;
	        }
			// PRLN("Pointer " << pointerId << " is " << touchPressed[pointerId] << " action "  << action);


        // }
	}




}
