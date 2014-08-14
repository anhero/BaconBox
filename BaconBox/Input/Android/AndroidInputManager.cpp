#include "BaconBox/PlatformFlagger.h"


#include "BaconBox/Input/Android/AndroidInputManager.h"
#include "BaconBox/Console.h"
#include "BaconBox/Display/Window/Android/AndroidMainWindow.h"
#include "BaconBox/Input/Pointer/Android/AndroidPointer.h"

#include "BaconBox/Helper/Android/AndroidHelper.h"

#include "BaconBox/Core/Engine.h"
#include "BaconBox/Core/Singleton.h"

using namespace BaconBox;

BB_SINGLETON_IMPL(AndroidInputManager);

// bool AndroidInputManager::isRunning() const {
// 	return running;
// }

AndroidInputManager::AndroidInputManager() : InputManager(){

	AndroidHelper::getAppState()->onInputEvent = handleInput;

}

AndroidInputManager::~AndroidInputManager() {

}


int32_t AndroidInputManager::handleInput(struct android_app* app, AInputEvent* event){
	if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {
      	((AndroidPointer*)getDefaultPointer())->receiveInput(app, event);
        return 1;
    }
    else{
		return 0;
    }
}

void AndroidInputManager::update() {
	InputManager::update();
}

