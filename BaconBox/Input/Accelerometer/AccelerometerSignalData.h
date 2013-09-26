/**
 * @file
 * @ingroup Input
 */
#ifndef BB_ACCELEROMETER_SIGNAL_DATA_H
#define BB_ACCELEROMETER_SIGNAL_DATA_H

#include "BaconBox/Input/InputSignalData.h"
#include "BaconBox/Input/Accelerometer/AccelerometerState.h"
#include "BaconBox/Property.h"

namespace BaconBox {
	/**
	 * Contains the data needed by slots that listen to the accelerometer(s)'s
	 * signals.
	 * @ingroup Input
	 */
	class AccelerometerSignalData : public InputSignalData {
	public:
		/**
		 * Parameterized constructor.
		 * @param newAccelerometerState State of the accelerometer device that
		 * is sending the signal.
		 */
		AccelerometerSignalData(const AccelerometerState& newAccelerometerState);
		
		/**
		 * Destructor.
		 */
		~AccelerometerSignalData();
		
		/// State of the accelerometer device that sent the signal.
		const AccelerometerState& accelerometerState;
		
		float getX() const;
		float getY() const;
		float getZ() const;

		
#ifdef SWIG
		float x;
		float y;
		float z;
#else
		Property<float, AccelerometerSignalData> x;
		Property<float, AccelerometerSignalData> y;
		Property<float, AccelerometerSignalData> z;
#endif



	};
}

#endif
