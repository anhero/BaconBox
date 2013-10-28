/**
 * @file
 * @ingroup Input
 */
#ifndef BB_ACCELEROMETER_STATE_H
#define BB_ACCELEROMETER_STATE_H

#include "BaconBox/Input/InputState.h"
#include "BaconBox/vmath.h"
namespace BaconBox {
	/**
	 * Contains the information about the accelerometer.
	 * @ingroup Input
	 */
	class AccelerometerState : public InputState {
		friend class Accelerometer;
	public:
		/**
		 * Default constructor.
		 */
		AccelerometerState();
		
		/**
		 * Destructor.
		 */
		~AccelerometerState();
		
		/**
		 * Gets the x acceleration.
		 * @return X acceleration.
		 */
		float getXAcceleration() const;
		
		/**
		 * Gets the y acceleration.
		 * @return Y acceleration.
		 */
		float getYAcceleration() const;
		
		/**
		 * Gets the z acceleration.
		 * @return Z acceleration.
		 */
		float getZAcceleration() const;
		
		const vmath::Vector3f & getAcceleration() const;

	private:
		/// Initial acceleration values.
		static const float STARTING_ACCELERATION;
		
		VMATH_NAMESPACE::Vector3f acceleration;

	};
}

#endif
