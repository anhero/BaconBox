/**
 * @file
 * @ingroup Display
 */
#ifndef BB_ANDROID_HELPER_H
#define BB_ANDROID_HELPER_H

#include <string>
#include <jni.h>
#include "BaconBox/Display/Window/Android/android_native_app_glue.h"
#include <android/asset_manager_jni.h>

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

		/// Gets a reference to the Android Asset Manager from native code only.
		static AAssetManager* getAssetManager();

		static struct android_app* appState;
	private:
		static std::string packageName;
		static std::string pathToAPK;
		/// Stashed Assets Manager for re-use.
		static AAssetManager* assets_manager;

	};

}
#endif
