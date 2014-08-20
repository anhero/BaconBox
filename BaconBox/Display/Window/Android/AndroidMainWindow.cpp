#include "AndroidMainWindow.h"

#include "BaconBox/Input/InputManager.h"
#include "BaconBox/Console.h"

#include "android_native_app_glue.h"
#include "BaconBox/Display/Driver/OpenGL/BBOpenGL.h"
#include "BaconBox/Core/Engine.h"
	#include "BaconBox/Helper/Android/AndroidHelper.h"
#include "BaconBox/Display/Driver/GraphicDriver.h"
#include <android/native_window.h>
#include "BaconBox/Audio/SoundEngine.h"
#include "BaconBox/Audio/MusicEngine.h"
#include "BaconBox/ResourceManager.h"

extern int main(int argc, char *argv[]);
// extern void startLuaGame();


namespace BaconBox {

	BB_SINGLETON_IMPL(AndroidMainWindow);

AndroidMainWindow * AndroidMainWindow::androidMainWindow = NULL;

bool AndroidMainWindow::animating =  false;

// Static values for later deferred initialization.
bool AndroidMainWindow::deferredInitializationDone = false;
EGLDisplay AndroidMainWindow::deferredDisplay = EGL_NO_DISPLAY;
EGLContext AndroidMainWindow::deferredContext = EGL_NO_CONTEXT;
EGLSurface AndroidMainWindow::deferredSurface = EGL_NO_SURFACE;


void AndroidMainWindow::onBaconBoxInit(unsigned int resolutionWidth,
			                  unsigned int resolutionHeight,
			                  float contextWidth,
			                  float contextHeight,
								WindowOrientation::type orientation){
		GraphicDriver::getInstance().initializeGraphicDriver();
		this->handleResize();

		InputManager::getInstance().setNbKeyboards(1);
		InputManager::getInstance().setNbPointers(1);
	}

	void AndroidMainWindow::initWindow(){
		if(needContext){
			needContext = false;
			display = deferredDisplay;
			context = deferredContext;
			surface = deferredSurface;
			glDisable(GL_DEPTH_TEST);
			animating = true;
		}
	}

	void AndroidMainWindow::handleResize() {
		EGLint w, h;
		eglQuerySurface(this->display, this->surface, EGL_WIDTH, &w);
		eglQuerySurface(this->display, this->surface, EGL_HEIGHT, &h);
		this->MainWindow::setResolution(w, h);
	}

	void AndroidMainWindow::deferredInitWindow() {
		if (deferredInitializationDone) {
			return;
		}

		const EGLint configAttribs[] = {
			EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
			EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
			EGL_BLUE_SIZE, 8,
			EGL_GREEN_SIZE, 8,
			EGL_RED_SIZE, 8,
			EGL_NONE
		};

		const EGLint contextAttribs[] = {
			EGL_CONTEXT_CLIENT_VERSION, 2,
			EGL_NONE
		};

		EGLint w, h, dummy, format;
		EGLint numConfigs;
		EGLConfig config;
		EGLSurface surface;
		EGLContext context;

		EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
		eglInitialize(display, 0, 0);
		eglChooseConfig(display, configAttribs, &config, 1, &numConfigs);
		eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);

		ANativeWindow_setBuffersGeometry(AndroidHelper::getAppState()->window, 0, 0, format);
		surface = eglCreateWindowSurface(display, config, AndroidHelper::getAppState()->window, NULL);
		context = eglCreateContext(display, config, NULL, contextAttribs);

		if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE) {
			Console__error("Unable to eglMakeCurrent");
		}

		eglQuerySurface(display, surface, EGL_WIDTH, &w);
		eglQuerySurface(display, surface, EGL_HEIGHT, &h);

		deferredDisplay = display;
		deferredContext = context;
		deferredSurface = surface;

		// Printing some general-purpose information.
		PRLN(" * GL version: " << 	glGetString(GL_VERSION));
		PRLN(" * GL context size: "	<< w << "x" << h);
		PRLN(" * GL vendor: " << 	glGetString(GL_VENDOR));
		PRLN(" * GL renderer: " << 	glGetString(GL_RENDERER));
	}

	void AndroidMainWindow::termWindow(){
		GraphicDriver::getInstance().tearGraphicDriver();
		needContext = true;
		 if (display != EGL_NO_DISPLAY) {
	        eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
	        if (context != EGL_NO_CONTEXT) {
	            eglDestroyContext(display, context);
	        }
	        if (surface != EGL_NO_SURFACE) {
	            eglDestroySurface(display, surface);
	        }
	        eglTerminate(display);
	    }
	    animating = false;
	    display = EGL_NO_DISPLAY;
	    context = EGL_NO_CONTEXT;
	    surface = EGL_NO_SURFACE;

		AndroidMainWindow::deferredInitializationDone = false;
		AndroidMainWindow::deferredDisplay = display;
	    AndroidMainWindow::deferredContext = context;
	    AndroidMainWindow::deferredSurface = surface;
	}

	void AndroidMainWindow::handleCmd(struct android_app* app, int32_t cmd) {

    switch (cmd) {
        case APP_CMD_SAVE_STATE:
            // The system has asked us to save our current state.  Do so.
        	PRLN("APP_CMD_SAVE_STATE");
			Engine::saveState.shoot();
            break;
        case APP_CMD_INIT_WINDOW:
        	PRLN("APP_CMD_INIT_WINDOW");
        	animating = true;
            // The window is being shown, get it ready.
        	if(AndroidHelper::getAppState()->window != NULL){
				AndroidMainWindow::deferredInitWindow();
			}
			else{
				Console__error("NO WINDOW");
			}
            break;
        case APP_CMD_TERM_WINDOW:
    	PRLN("APP_CMD_TERM_WINDOW");
			// The window is being hidden or closed, clean it up.
			// AndroidHelper::getAppState()->destroyRequested = 1;
			// BaconBox::LuaManager::destroyVM();
    		AndroidMainWindow::getInstance().termWindow();
            break;
		case APP_CMD_WINDOW_RESIZED:
			AndroidMainWindow::getInstance().handleResize();
			break;
        case APP_CMD_GAINED_FOCUS:
        PRLN("APP_CMD_GAINED_FOCUS");
            // When our app gains focus, we start monitoring the accelerometer.
        	animating = true;
            // AndroidMainWindow * mainWindow = reinterpret_cast<AndroidMainWindow*>(&AndroidMainWindow::getInstance());
			if (Engine::isReady()) {
				Engine::getMusicEngine().setMuted(androidMainWindow->musicMuted);
				Engine::getSoundEngine().setMuted(androidMainWindow->soundMuted);
			}
            break;
        case APP_CMD_LOST_FOCUS:
	        PRLN("APP_CMD_LOST_FOCUS");

            // When our app loses focus, we stop monitoring the accelerometer.
            // This is to avoid consuming battery while not being used.
            // AndroidMainWindow * mainWindow = reinterpret_cast<AndroidMainWindow*>(&AndroidMainWindow::getInstance());
            androidMainWindow->musicMuted = Engine::getMusicEngine().isMuted();
            androidMainWindow->soundMuted = Engine::getSoundEngine().isMuted();
            Engine::getMusicEngine().setMuted(true);
            Engine::getSoundEngine().setMuted(true);
            PV(Engine::getMusicEngine().isMuted());
        	animating = false;
            break;

		// Commands for which we do not do anything.
		case APP_CMD_START:
			PRLN("APP_CMD_START");
			break;
		case APP_CMD_LOW_MEMORY:
			PRLN("APP_CMD_LOW_MEMORY");
			break;
		case APP_CMD_CONFIG_CHANGED:
			PRLN("APP_CMD_CONFIG_CHANGED");
			break;
		case APP_CMD_RESUME:
			PRLN("APP_CMD_RESUME");
			break;
		case APP_CMD_PAUSE:
			PRLN("APP_CMD_PAUSE");
			break;

		case APP_CMD_STOP:
			PRLN("APP_CMD_STOP");
			break;
		case APP_CMD_DESTROY:
			PRLN("APP_CMD_DESTROY");
			break;
		default:
		    PRLN("APP_CMD_ AndroidMainWindow::handleCmd HIT DEFAULT " << cmd);
		break;

    }
}





	void AndroidMainWindow::setUpdatesPerSecond(double setFrameInterval){}



// void term_display(struct engine* engine) {
//     if (engine->display != EGL_NO_DISPLAY) {
//         eglMakeCurrent(engine->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
//         if (engine->context != EGL_NO_CONTEXT) {
//             eglDestroyContext(engine->display, engine->context);
//         }
//         if (engine->surface != EGL_NO_SURFACE) {
//             eglDestroySurface(engine->display, engine->surface);
//         }
//         eglTerminate(engine->display);
//     }
//     engine->animating = 0;
//     engine->display = EGL_NO_DISPLAY;
//     engine->context = EGL_NO_CONTEXT;
//     engine->surface = EGL_NO_SURFACE;
// }

	void AndroidMainWindow::loop(){
       struct android_poll_source* source;
	    int ident;
        int events;
		while(true){

			while ((ident=ALooper_pollAll( 0 , NULL, &events,
			(void**)&source)) >= 0) {

	            // Process this event.
	            if (source != NULL) {
	                source->process(AndroidHelper::getAppState(), source);
	            }

	            // // If a sensor has data, process it now.
	            // if (ident == LOOPER_ID_USER) {
	            //     if (engine.accelerometerSensor != NULL) {
	            //         ASensorEvent event;
	            //         while (ASensorEventQueue_getEvents(engine.sensorEventQueue,
	            //                 &event, 1) > 0) {
	            //             LOGI("accelerometer: x=%f y=%f z=%f",
	            //                     event.acceleration.x, event.acceleration.y,
	            //                     event.acceleration.z);
	            //         }
	            //     }
	            // }

	            // // Check if we are exiting.
	            // if (state->destroyRequested != 0) {
	            //     engine_term_display(&engine);
	            //     return;
	            // }
	        }

	        if (AndroidHelper::getAppState()->destroyRequested != 0) {
                // engine_term_display(&engine);
                PRLN("Destroy requested returning from game loop");
                return;
            }

    		if(androidMainWindow && animating && !androidMainWindow->needContext && androidMainWindow->display){
					Engine::pulse();
					// PRLN("LOOPING");
				if (!Engine::isBufferSwapped()) {
					// PV((glGetError() == GL_NO_ERROR));
					eglSwapBuffers(androidMainWindow->display, androidMainWindow->surface);
					Engine::setBufferSwapped();
				}

			}
			else if(androidMainWindow && animating && androidMainWindow->needContext){
				androidMainWindow->initWindow();
				Engine::getGraphicDriver().initializeGraphicDriver();
			}
			else{
				// PRLN("NOT DOING STUFF");
				// PV(androidMainWindow);PV(animating);PV(androidMainWindow);PV(androidMainWindow->needContext);PV(androidMainWindow->display);
			}
		}
	}

	void AndroidMainWindow::show() {
 		loop();
	}


	void AndroidMainWindow::setResolution(unsigned int resolutionWidth,
	                                  unsigned int resolutionHeight) {
		GraphicDriver::getInstance().initializeGraphicDriver();
	}

	void AndroidMainWindow::setContextSize(float newContextWidth,
	                                   float newContextHeight) {
		this->MainWindow::setContextSize(newContextWidth, newContextHeight);
//		GraphicDriver::getInstance().initializeGraphicDriver();
	}

	void AndroidMainWindow::setCaption(const std::string &caption) {
	}

	bool AndroidMainWindow::isFullScreen() const {
		return false;
	}

	void AndroidMainWindow::setFullScreen(bool newFullScreen) {
	}

	bool AndroidMainWindow::isInputGrabbed() const {
		return false;
	}

	void AndroidMainWindow::setInputGrabbed(bool newInputGrabbed) {
	}

	AndroidMainWindow::AndroidMainWindow() : MainWindow(), display(NULL), surface(NULL), context(NULL), needContext(true){
		androidMainWindow = this;
		this->initWindow();
	}

	AndroidMainWindow::~AndroidMainWindow() {
	}
    
    void AndroidMainWindow::hideCursor(){
    }
    
    void AndroidMainWindow::showCursor(){
    }
}
