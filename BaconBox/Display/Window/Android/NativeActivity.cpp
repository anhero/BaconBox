/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

//BEGIN_INCLUDE(all)
#include <jni.h>
#include <errno.h>

#include <EGL/egl.h>
// #include <GLES/gl.h>

#include <android/sensor.h>
#include <android/log.h>
#include "android_native_app_glue.h"

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-activity", __VA_ARGS__))

#include "BaconBox/Display/Window/Android/AndroidMainWindow.h"
#include "BaconBox/Console.h"
	#include "BaconBox/Helper/Android/AndroidHelper.h"
    #include "BaconBox/Input/Android/AndroidInputManager.h"

extern "C" void engine_handle_cmd(struct android_app* app, int32_t cmd) {
    PRLN("engine_handle_cmd  -----");

}

extern "C" int32_t engine_handle_input(struct android_app* app, AInputEvent* event) {



    return 1;
}
extern int main(int argc, char *argv[]);
// extern void clean();

extern "C" void android_main(struct android_app* state) {
    BaconBox::AndroidHelper::appState = state;
    BaconBox::AndroidHelper::getAppState()->window = NULL;
   	//state->onAppCmd = engine_handle_cmd;
	state->onAppCmd = BaconBox::AndroidMainWindow::handleCmd;

    app_dummy();
    // BaconBox::AndroidMainWindow::loop();
    // clean();
        struct android_poll_source* source;
	    int ident;
        int events;
        while(BaconBox::AndroidHelper::getAppState()->window  == NULL){
			while ((ident=ALooper_pollAll( 0 , NULL, &events,
			(void**)&source)) >= 0) {

	            if (source != NULL) {
	                source->process(BaconBox::AndroidHelper::getAppState(), source);
	            }
	        }
    	}
   //  PRLN("starting main!!!!");

    main(0, NULL);
}
//END_INCLUDE(all)
