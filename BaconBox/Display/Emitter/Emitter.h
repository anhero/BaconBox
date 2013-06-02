#ifndef BB_EMITTER_H
#define BB_EMITTER_H

namespace BaconBox {
	class Emitter {
	public:
		static const int NONE = 0;
		static const int CLOCKWISE = 1;
		static const int COUNTER_CLOCKWISE = 2;
		static const int BOTH = CLOCKWISE | COUNTER_CLOCKWISE;
		
		Emitter();
		
		Emitter(const Emitter &src);
		
		virtual ~Emitter();
		
		Emitter &operator=(const Emitter &src);
	private:
		/**
		 * The minimum lifetime of each particle, measured in seconds.
		 */
		double minLifetime;
		
		/**
		 * The maximum lifetime of each particle, measured in seconds.
		 */
		double maxLifetime;
		
		/**
		 * Minimum force applied to the particle when spawned.
		 */
		float minForce;
		
		/**
		 * Maximum force applied to the particle when spawned.
		 */
		float maxForce;
		
		/**
		 * Minimum angle at which each particle is spawned. The angle is between
		 * -180 and 180. Angle increases as it goes counter clockwise.
		 */
		float minAngle;
		
		/**
		 * Maximum angle at which each particle is spawned. The angle is between
		 * -180 and 180. Angle increases as it goes counter clockwise.
		 */
		float angleVariation;
		
		/**
		 * Minimum rotation speed (measured in degrees) to apply to each
		 * particle spawned.
		 */
		float minAngularVelocity;
		
		/**
		 * Maximum rotation speed (measured in degrees) to apply to each
		 * particle spawned.
		 */
		float maxAngularVelocity;
		
		/**
		 * Rotation direction for each particle spawned. Either NONE, CLOCKWISE
		 * COUNTER_CLOCKWISE or BOTH.
		 */
		int rotationDirection;
	};
}

#endif /* defined(BB_EMITTER_H) */

