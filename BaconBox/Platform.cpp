#include "Platform.h"
#include "BaconBox/PlatformFlagger.h"
using namespace BaconBox;

Platform::Platform(){
	isRetina = false;
	isIOS = false;
	isIphone = false;
	isIphone5 = false;
	isIpad = false;
	isFlash = false;
#ifdef BB_IPHONE_PLATFORM
	isIOS = true;
#endif
	
	
#ifdef BB_FLASH_PLATFORM
	isFlash = true;
#endif
}


Platform &Platform::getInstance() {
	static Platform instance;
	return instance;
}


