/**
 * @file
 * @ingroup Input
 */
#ifndef BB_NULL_ACCELEROMETER_H
#define BB_NULL_ACCELEROMETER_H

#include "BaconBox/Input/Accelerometer/Accelerometer.h"

namespace BaconBox {
	/**
	 * Null accelerometer device. Used when the platform doesn't have an
	 * accelerometer device.
	 * @ingroup Input
	 */
	class NullAccelerometer : public Accelerometer {
	public:
		/**
		 * Default constructor.
		 */
		NullAccelerometer();

		/**
		 * Destructor.
		 */
		~NullAccelerometer();

		/**
		 * Update the null accelerometer device.
		 */
		void updateDevice();
	};

}

#endif // BB_NULL_ACCELEROMETER_H
