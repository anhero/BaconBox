#include "BaconBox/Helper/Android/AndroidHelper.h"
#include "BaconBox/Console.h"

using namespace BaconBox;

std::string AndroidHelper::packageName = std::string();
std::string AndroidHelper::pathToAPK = std::string();
struct android_app* AndroidHelper::appState = NULL;


	struct android_app* AndroidHelper::getAppState(){
		return appState;
	}


	const std::string & AndroidHelper::getPackageName(){
		if(packageName ==""){
		    JNIEnv* env=0;

			ANativeActivity* activity = appState->activity;
		    (activity->vm)->AttachCurrentThread(&env, 0);

		    jclass clazz = env->GetObjectClass(activity->clazz);
		    jmethodID methodID = env->GetMethodID(clazz, "getPackageName", "()Ljava/lang/String;");
		    jobject result = env->CallObjectMethod(activity->clazz, methodID);
		    const char* str;
		    jboolean isCopy;
		    str = env->GetStringUTFChars((jstring)result, &isCopy);
		    if(str)packageName.assign(str);
		    env->ReleaseStringUTFChars((jstring)result, str);

		    activity->vm->DetachCurrentThread();
		}
		return packageName;
	}

	const std::string & AndroidHelper::getPathToAPK(){
		if(pathToAPK == ""){
		    JNIEnv* env=0;

			ANativeActivity* activity = appState->activity;
		    (activity->vm)->AttachCurrentThread(&env, 0);

		    jclass clazz = env->GetObjectClass(activity->clazz);
		    jmethodID methodID = env->GetMethodID(clazz, "getPackageCodePath", "()Ljava/lang/String;");
		    jobject result = env->CallObjectMethod(activity->clazz, methodID);
		    const char* str;
		    jboolean isCopy;
		    str = env->GetStringUTFChars((jstring)result, &isCopy);
		    if(str)pathToAPK.assign(str);
		    env->ReleaseStringUTFChars((jstring)result, str);
		    activity->vm->DetachCurrentThread();
		}
		return pathToAPK;
	}

	JNIEnv* AndroidHelper::getJavaEnv(){
		return appState->activity->env;
	}

	JavaVM* AndroidHelper::getJavaVM(){
		return appState->activity->vm;
	}
	

	jclass AndroidHelper::findClass(const std::string & className, JNIEnv *jni){
		//Got this from: http://hi.baidu.com/letsherwel/item/23577c081e3b107fbfe97e23
		jclass activityClass = jni->FindClass("android/app/NativeActivity");
		jmethodID getClassLoader = jni->GetMethodID(activityClass,"getClassLoader", "()Ljava/lang/ClassLoader;");
		jobject cls = jni->CallObjectMethod(appState->activity->clazz, getClassLoader);
		jclass classLoader = jni->FindClass("java/lang/ClassLoader");
		jmethodID findClass = jni->GetMethodID(classLoader, "loadClass", "(Ljava/lang/String;)Ljava/lang/Class;");
		jstring strClassName = jni->NewStringUTF(className.c_str());
		jclass classIWant = (jclass)jni->CallObjectMethod(cls, findClass, strClassName);
		jni->DeleteLocalRef(strClassName);
		return classIWant;
	}



