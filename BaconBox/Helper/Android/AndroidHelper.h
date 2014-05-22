/**
 * @file
 * @ingroup Display
 */
#ifndef BB_ANDROID_HELPER_H
#define BB_ANDROID_HELPER_H

 	#include <string>
#include <jni.h>
#include "BaconBox/Display/Window/Android/android_native_app_glue.h"

struct android_app;
namespace BaconBox {

	class AndroidHelper {
	public:
		static const std::string & getPackageName();
		static const std::string & getPathToAPK();
		static struct android_app* getAppState();
		static JNIEnv* getJavaEnv();
		static JavaVM* getJavaVM();
		static jclass findClass(const std::string & className, JNIEnv *jni);

		static struct android_app* appState;
	private:
		static std::string packageName;
		static std::string pathToAPK;

	};

}
#endif
