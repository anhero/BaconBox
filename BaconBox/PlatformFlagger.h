#ifndef BB_PLATFORM_FLAGGER_H
#define BB_PLATFORM_FLAGGER_H

/*******************************************************************************
 * Basic platform defines/detection
 **************************************************************************** */
#ifdef QT
	#ifndef BB_QT
		#define BB_QT
	#endif
#endif // QT

#ifdef SDL
	#define BB_SDL
#endif


/*******************************************************************************
 * System-specific defines
 ******************************************************************************/
//Android platform
#ifdef __ANDROID__
	#define BB_ANDROID
	#define BB_OPENGLES
#endif // __ANDROID__

//Linux systems
#ifdef linux
	#define BB_LINUX

	#define BB_TIME_HELPER_IMPL BaconBox::LibcTimeHelper
	#define BB_TIME_HELPER_INCLUDE "BaconBox/Helper/libc/LibcTimeHelper.h"

	#ifndef BB_ANDROID
		#define BB_HAS_GCC_STACKTRACE
	#endif
#endif // linux

//Windows systems
#if defined(_WIN32) || defined(__CYGWIN__)
	#ifdef BB_QT
		#include <qt_windows.h>
	#endif // BB_QT

	#define BB_WINDOWS_PLATFORM


	#define BB_TIME_HELPER_IMPL BaconBox::WindowsTimeHelper
	#define BB_TIME_HELPER_INCLUDE "BaconBox/Helper/Windows/WindowsTimeHelper.h"
#endif // _WIN32



//Apple systems
#ifdef __APPLE__
	//Get more informations about the system
	#include "TargetConditionals.h"

	#define BB_APPLE_PLATFORM
    

	//More detailed platforms
	#if TARGET_IPHONE_SIMULATOR
		#define BB_IPHONE_PLATFORM
		#define BB_IPHONE_SIMULATOR_PLATFORM
	#endif // TARGET_IPHONE_SIMULATOR

	#if TARGET_OS_IPHONE
		#define BB_IPHONE_PLATFORM
		#define BB_IPHONE_DEVICE_PLATFORM
	#endif // TARGET_OS_IPHONE

	#if TARGET_OS_MAC
		#define BB_MAC_PLATFORM
	#endif

	#ifdef BB_IPHONE_PLATFORM
        #define BB_OPENGLES
		//Time on iOS
		#define BB_TIME_HELPER_IMPL BaconBox::IOSTimeHelper
		#define BB_TIME_HELPER_INCLUDE "BaconBox/Helper/ios/IOSTimeHelper.h"
	#elif defined(BB_MAC_PLATFORM)
        #define BB_OPENGL
		// Time on Mac OS X
		#define BB_TIME_HELPER_IMPL BaconBox::LibcTimeHelper
		#define BB_TIME_HELPER_INCLUDE "BaconBox/Helper/libc/LibcTimeHelper.h"
	#endif

	#define BB_HAS_GCC_STACKTRACE
#endif // __APPLE__

/*******************************************************************************
 * Platform-specific defines
 ******************************************************************************/

//SDL platform
#ifdef BB_SDL
	//Graphics engine for SDL
	#define BB_OPENGL

	//Sound engine for SDL
	#define BB_SOUND_ENGINE_IMPL new SDLMixerEngine()
	#define BB_SOUND_ENGINE_INCLUDE "BaconBox/Audio/SDL/SDLMixerEngine.h"

	#define BB_MUSIC_ENGINE_IMPL SDLMixerEngine::getInstance()
	#define BB_MUSIC_ENGINE_INCLUDE "BaconBox/Audio/SDL/SDLMixerEngine.h"

	//Input engine for SDL
	#define BB_KEYBOARD_IMPL new SDLKeyboard()
	#define BB_KEYBOARD_INCLUDE "BaconBox/Input/Keyboard/SDL/SDLKeyboard.h"

	#define BB_POINTER_IMPL new SDLPointer()
	#define BB_POINTER_INCLUDE "BaconBox/Input/Pointer/SDL/SDLPointer.h"

    #define BB_GAME_PAD_IMPL new SDLGamePad(i)
    #define BB_GAME_PAD_INCLUDE "BaconBox/Input/GamePad/SDL/SDLGamePad.h"

	#define BB_INPUT_MANAGER_IMPL BaconBox::SDLInputManager
	#define BB_INPUT_MANAGER_INCLUDE "BaconBox/Input/SDL/SDLInputManager.h"

	#define BB_MAIN_WINDOW_IMPL new SDLMainWindow()
	#define BB_MAIN_WINDOW_INCLUDE "BaconBox/Display/Window/SDL/SDLMainWindow.h"


#endif // BB_SDL

//Qt platform
#ifdef BB_QT
	//Graphics engine for Qt
	#define BB_OPENGL

	//Sound engine for Qt
	#define BB_OPENAL
	#define BB_SOUND_ENGINE_IMPL new OpenALEngine()
	#define BB_SOUND_ENGINE_INCLUDE "BaconBox/Audio/OpenAL/OpenALEngine.h"

	//Input engine for Qt
	#define BB_KEYBOARD_IMPL new QtKeyboard()
	#define BB_KEYBOARD_INCLUDE "BaconBox/Input/Keyboard/Qt/QtKeyboard.h"

	#define BB_POINTER_IMPL new QtPointer()
	#define BB_POINTER_INCLUDE "BaconBox/Input/Pointer/Qt/QtPointer.h"

	#define BB_MAIN_WINDOW_IMPL new QtMainWindow()
	#define BB_MAIN_WINDOW_INCLUDE "BaconBox/Display/Window/Qt/QtMainWindow.h"
#endif // BB_QT

//iOS platform
#ifdef BB_IPHONE_PLATFORM
	//Sound engine for iOS
	#define BB_OPENAL
	#define BB_SOUND_ENGINE_IMPL new OpenALEngine()
	#define BB_SOUND_ENGINE_INCLUDE "BaconBox/Audio/OpenAL/OpenALEngine.h"

	//Music engine for iOS
	#define BB_AV_AUDIO_PLAYER
	#define BB_MUSIC_ENGINE_IMPL new RBAudioPlayerEngine()
	#define BB_MUSIC_ENGINE_INCLUDE "BaconBox/Audio/ios/RBAudioPlayerEngine.h"


	//Input engine for iOS
	#define BB_POINTER_INCLUDE "IOSPointer.h"
	#define BB_POINTER_IMPL new IOSPointer()

	#define BB_MAIN_WINDOW_IMPL new IOSMainWindow()
	#define BB_MAIN_WINDOW_INCLUDE "BaconBox/Input/Pointer/ios/IOSMainWindow.h"
#endif // BB_IPHONE_PLATFORM

#if defined (BB_OPENGL) || defined (BB_OPENGLES)
	#define BB_GRAPHIC_DRIVER_IMPL new OpenGLDriver()
	#define BB_GRAPHIC_DRIVER_INCLUDE "BaconBox/Display/Driver/OpenGL/OpenGLDriver.h"
#endif

/*
//Mac platform (without SDL or Qt) (currently unsupported)
//TODO: Support mac platform with cocoa only and related defines
#if defined(BB_MAC_PLATFORM)
	#if defined(BB_QT)
		#define BB_MUSIC_ENGINE_IMPL NULL
	#else
		#define BB_MUSIC_ENGINE_INCLUDE "RBAudioPlayerEngine.h"
		#define BB_MUSIC_ENGINE_IMPL new RBAudioPlayerEngine()
	#endif
#endif
*/


/*******************************************************************************
 * Defaulting implementations if not defined
 ******************************************************************************/

// For NULL inputs
#ifndef BB_POINTER_IMPL
	#define BB_POINTER_IMPL new NullPointer()
	#define BB_POINTER_INCLUDE "BaconBox/Input/Pointer/NullPointer.h"
#endif
#ifndef BB_KEYBOARD_IMPL
	#define BB_KEYBOARD_IMPL new NullKeyboard()
	#define BB_KEYBOARD_INCLUDE "BaconBox/Input/Keyboard/NullKeyboard.h"
#endif
#ifndef BB_ACCELEROMETER_IMPL
	#define BB_ACCELEROMETER_IMPL new NullAccelerometer()
	#define BB_ACCELEROMETER_INCLUDE "BaconBox/Input/Accelerometer/NullAccelerometer.h"
#endif
#ifndef BB_GAME_PAD_IMPL
	#define BB_GAME_PAD_IMPL NULL
#endif

// For NULL main window.
#ifndef BB_MAIN_WINDOW_IMPL
	#define BB_MAIN_WINDOW_IMPL new NullMainWindow()
	#define BB_MAIN_WINDOW_INCLUDE "NullMainWindow.h"
#endif

// For NULL sound engine
#ifndef BB_SOUND_ENGINE_IMPL
	#define BB_SOUND_ENGINE_IMPL new NullAudioEngine()
	#define BB_SOUND_ENGINE_INCLUDE "BaconBox/Audio/NullAudioEngine.h"
#endif // BB_SOUND_ENGINE_IMPL

// For NULL music engine
#ifndef BB_MUSIC_ENGINE_IMPL
	#define BB_MUSIC_ENGINE_IMPL new NullAudioEngine()
	#define BB_MUSIC_ENGINE_INCLUDE "BaconBox/Audio/NullAudioEngine.h"
#endif // BB_MUSIC_ENGINE_IMPL

// For NULL graphic driver.
#ifndef BB_GRAPHIC_DRIVER_IMPL
	#define BB_GRAPHIC_DRIVER_IMPL new NullGraphicDriver()
	#define BB_GRAPHIC_DRIVER_INCLUDE "BaconBox/Display/Driver/NullGraphicDriver.h"
#endif

// Default input manager
#ifndef BB_INPUT_MANAGER_IMPL
	#define BB_INPUT_MANAGER_IMPL BaconBox::InputManager
#endif

#endif // BB_PLATFORM_FLAGGER_H
