/**
 * @file
 * @ingroup Input
 */
#ifndef BB_FLASHPOINTER_H
#define BB_FLASHPOINTER_H

#include "BaconBox/Input/Pointer/Pointer.h"
#include <AS3/AS3.h>
#include <AS3/AS3++.h>

namespace BaconBox {

	class FlashPointer : public Pointer {
		friend class InputManager;
	protected:
		/**
		 * Default constructor.
		 */
		FlashPointer();
		
		/**
		 * Destructor.
		 */
		~FlashPointer();
	
		void updateDevice();

	private:

		AS3::local::var mouseUpFun;
		void pointerUpCallBack(AS3::local::var event);
		static AS3::local::var mouseUpEventListener(void *arg, AS3::local::var as3Args);

		AS3::local::var mouseDownFun;
		void pointerDownCallBack(AS3::local::var event);
		static AS3::local::var mouseDownEventListener(void *arg, AS3::local::var as3Args);

		AS3::local::var mouseMoveFun;
		void pointerMoveCallBack(AS3::local::var event);
		static AS3::local::var mouseMoveEventListener(void *arg, AS3::local::var as3Args);

	};
}

#endif
