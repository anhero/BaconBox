#include "BaconBox/PlatformFlagger.h"

#ifdef BB_IPHONE_PLATFORM

#include "BaconBox/Helper/ios/IOSTimeHelper.h"

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

using namespace BaconBox;

void IOSTimeHelper::sleep(double duration) {
	[NSThread sleepForTimeInterval : duration];
}

IOSTimeHelper::IOSTimeHelper() : TimeHelper(), startTime(0.0), lastTime(0.0) {
	startTime = [[NSDate date] timeIntervalSince1970];
}

IOSTimeHelper::~IOSTimeHelper() {
}

void IOSTimeHelper::refreshTime() {
	double currentTime = [[NSDate date] timeIntervalSince1970];
	double sinceLast = currentTime - lastTime;
	
	// We add time to sinceStart and sinceStartReal only if the game isn't
	// paused.
	if(!isPaused()) {
		// We add this time to sinceStart while taking into account the time
		// scaling.
		sinceStart += sinceLast * getTimeScale();
		// We add this time to the sinceStartReal.
		sinceStartReal += sinceLast;
	}
	
	// We calculate the time since the game started.
	sinceStartComplete += sinceLast;
	
	lastTime = currentTime;
}

#endif
