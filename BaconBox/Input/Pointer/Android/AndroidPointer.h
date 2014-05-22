/**
 * @file
 * @ingroup Input
 */
#ifndef BB_ANDROID_POINTER_H
#define BB_ANDROID_POINTER_H


#include <vector>
#include "BaconBox/Input/Pointer/Pointer.h"
#include <sigly.h>
#include "BaconBox/Display/Window/Android/android_native_app_glue.h"

namespace BaconBox {

	class AndroidPointer : public Pointer, public sigly::HasSlots<> {
		friend class AndroidInputManager;
		friend class InputManager;
	public:

	protected:
		/**
		 * Default constructor.
		 */
		AndroidPointer();
		
		/**
		 * Destructor.
		 */
		~AndroidPointer();
		
		/**
		 * Updates the input device information.
		 */
		void updateDevice();
	private:
		void receiveInput(struct android_app* app, AInputEvent* event);
		std::vector<Vector2> touchPos;
		std::vector<bool> touchPressed;
		
	};
}

#endif

