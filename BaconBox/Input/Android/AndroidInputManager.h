/**
 * @file
 * @ingroup Input
 */
#ifndef BB_ANDROID_INPUT_MANAGER_H
#define BB_ANDROID_INPUT_MANAGER_H

#include "BaconBox/PlatformFlagger.h"


#include "BaconBox/Input/InputManager.h"

#include "BaconBox/Display/Window/Android/android_native_app_glue.h"

namespace BaconBox {
	class AndroidInputManager : public InputManager {
		friend class InputManager;
		BB_SINGLETON_DECL(AndroidInputManager);
	protected:
		AndroidInputManager();
		~AndroidInputManager();
		void update();
	private:
		static int32_t handleInput(struct android_app* app, AInputEvent* event);
		// struct android_app* appState;

	};
}

#endif
