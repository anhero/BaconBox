#include "URL.h"
#include "BaconBox/PlatformFlagger.h"
#ifdef BB_IPHONE_PLATFORM
#import <UIKit/UIKit.h>
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
