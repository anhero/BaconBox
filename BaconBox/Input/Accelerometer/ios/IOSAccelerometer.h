/**
 * @file
 * @ingroup Input
 */
#ifndef BB_IOS_ACCELEROMETER_H
#define BB_IOS_ACCELEROMETER_H

#include "BaconBox/Input/Accelerometer/Accelerometer.h"
#import <CoreMotion/CoreMotion.h>
namespace BaconBox {
	/**
	 * Null accelerometer device. Used when the platform doesn't have an
	 * accelerometer device.
	 * @ingroup Input
	 */
	class IOSAccelerometer : public Accelerometer, public sigly::HasSlots<> {
	public:
		/**
		 * Default constructor.
		 */
		IOSAccelerometer();

		/**
		 * Destructor.
		 */
//		~IOSAccelerometer();

		/**
		 * Update the null accelerometer device.
		 */
		void updateDevice();
		
	private:
		void onAccelData(CMAcceleration *accelData);

	};

}

#endif // BB_IOS_ACCELEROMETER_H
