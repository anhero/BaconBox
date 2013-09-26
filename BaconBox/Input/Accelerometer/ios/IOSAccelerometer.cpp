#include "BaconBox/Input/Accelerometer/ios/IOSAccelerometer.H"
#include "EAGLView.h"
#include "BaconBox/Display/Window/ios/BaconBoxAppAppDelegate.h"
#include "BaconBox/Display/Window/ios/BaconBoxAppViewController.h"

namespace BaconBox {
	IOSAccelerometer::IOSAccelerometer() : Accelerometer(), sigly::HasSlots<>() {
		[BaconBoxAppAppDelegate getViewController].accelData->connect(this, &IOSAccelerometer::onAccelData);
	}

//	IOSAccelerometer::~IOSAccelerometer() {
//		
//	}

	void IOSAccelerometer::updateDevice() {
		
	}
	
	void IOSAccelerometer::onAccelData(CMAcceleration *accelData){
		if(isActive() ){
			setState(accelData->x, accelData->y, accelData->z);
			if(areSignalsActive()){
				AccelerometerSignalData test(state);
				this->change.shoot(test);
			}
		}
	}

}
