#include "Platform.h"
#include "BaconBox/PlatformFlagger.h"
#ifdef BB_IPHONE_PLATFORM
#include <UIKit/UIDevice.h>
#include <UIKit/UIScreen.h>
#include <iostream>
#endif

using namespace BaconBox;

Platform::Platform(){
	isRetina = false;
	isIOS = false;
	isIphone = false;
	isIpod = false;
	isIphone5 = false;
	isIpad = false;
	isFlash = false;
#ifdef BB_IPHONE_PLATFORM
	isIOS = true;
	NSString * device = [UIDevice currentDevice].model;
	isIpad = [device  isEqual: @"iPad"];
	isIpod = [device  isEqual: @"Pod touch"];

	isIphone = [device  isEqual: @"iPhone"];
	isIphone5 = [[ UIScreen mainScreen ] bounds ].size.height == 568;
#endif
	
	
	
#ifdef BB_FLASH_PLATFORM
	isFlash = true;
#endif
}


Platform &Platform::getInstance() {
	static Platform instance;
	return instance;
}


