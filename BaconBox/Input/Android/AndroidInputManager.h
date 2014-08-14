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
	public:
		static AndroidInputManager& getInstance();
		void destroyInstance();

	protected:
		AndroidInputManager();
		~AndroidInputManager();
		void update();
		static AndroidInputManager * instance;
	private:
		static int32_t handleInput(struct android_app* app, AInputEvent* event);
		// struct android_app* appState;

	};
}

#endif
