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
	isIOSWide = false;
	isIpad = false;
	isFlash = false;
	isMobile = false;

#ifdef BB_IPHONE_PLATFORM
	
	NSString * device = [UIDevice currentDevice].model;
	this->isIOS = true;

	isIpad = [device  isEqual: @"iPad"];
	isIpod = [device  isEqual: @"Pod touch"];
	isRetina = [[UIScreen mainScreen] scale] == 2;
	isIphone = [device  isEqual: @"iPhone"];
	isIOSWide = [[ UIScreen mainScreen ] bounds ].size.height == 568;
	isMobile = true;
#endif
	
	
	
#ifdef BB_FLASH_PLATFORM
	isFlash = true;
#endif
}


Platform &Platform::getInstance() {
	static Platform instance;
	return instance;
}


