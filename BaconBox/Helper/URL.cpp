#include "URL.h"
#include "BaconBox/PlatformFlagger.h"
#ifdef BB_IPHONE_PLATFORM
#import <UIKit/UIKit.h>
#endif
#include "BaconBox/Console.h"

#ifdef BB_FLASH_PLATFORM
	#include "BaconBox/Core/Flash/FlashEngine.h"
	#include "BaconBox/Helper/Flash/FlashHelper.h"
	#include <AS3/AS3.h>
	#include <AS3/AS3++.h>
#endif

using namespace BaconBox;

bool URL::open(const std::string & url){
#ifdef BB_IPHONE_PLATFORM
	NSString * url_nsstring = [NSString stringWithCString:url.c_str() encoding:NSUTF8StringEncoding];
	url_nsstring = [url_nsstring stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
	NSURL * url_nsurl = [NSURL URLWithString:url_nsstring];
	if(![[UIApplication sharedApplication] canOpenURL:url_nsurl]) return false;
	[[UIApplication sharedApplication] openURL:url_nsurl];
		 return true;
#endif
		 return false;
}


std::string URL::getURL(){
	#ifdef BB_FLASH_PLATFORM	

		AS3::local::var stage = FlashEngine::getStage();
		AS3::local::var tempAS3URL = FlashHelper::getProperty(FlashHelper::getProperty(stage, "loaderInfo"), "url");

		char *temp = NULL;
	    std::string url = AS3::sz2stringAndFree(AS3::local::internal::utf8_toString(tempAS3URL));
	    return url;

    #else
	    PRLN("Method URL::getURL stubbed for the current platform");
	    return "Method URL::getURL stubbed for the current platform";
	#endif
}