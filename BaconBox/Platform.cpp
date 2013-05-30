#include "Platform.h"
#include "BaconBox/PlatformFlagger.h"
using namespace BaconBox;

Platform::Platform(){
	iphonePlatform = false;
	flashPlatform = false;
	
#ifdef BB_IPHONE_PLATFORM
	iphonePlatform = true;
#endif
	
	
#ifdef BB_IPHONE_PLATFORM
	flashPlatform = false;
#endif
}


bool Platform::isIphone(){
	return getInstance().iphonePlatform;
}
bool Platform::isFlash(){
	return getInstance().flashPlatform;
}

Platform &Platform::getInstance() {
	static Platform instance;
	return instance;
}


