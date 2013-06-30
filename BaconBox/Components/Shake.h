#ifndef BB_SHAKE_H
#define BB_SHAKE_H

#include "BaconBox/Core/Component.h"
#include "BaconBox/Helper/Stopwatch.h"
#include "BaconBox/Vector2.h"

namespace BaconBox {
	class Shake : public Component {
	public:
		enum ShakeAxis {
		    HORIZONTAL = 1,
		    VERTICAL = 2,
		    BOTH = 3
		};

		BB_ID_HEADER;

		static int MESSAGE_START_SHAKE;

		Shake();

		Shake(const Shake &src);

		virtual ~Shake();

		Shake &operator=(const Shake &src);

		virtual Shake *clone() const;

		virtual void receiveMessage(int senderID, int destID, int message, void *data);

		void update();

		void shake(float newIntensity = 0.05f, double newDuration = 0.5,
		           bool forceReset = true, ShakeAxis newAxis = BOTH);
		
		const Vector2 &getOffset() const;
	private:
		/// Axis on which the shaking takes place.
		ShakeAxis axis;

		/**
		 * Camera shaking intensity. Value between 0.0f and 1.0f. A ratio of
		 * the screen size.
		 */
		float intensity;

		/// Time the shaking must take before stopping.
		double duration;

		/// Offset used when the camera is shaking.
		Vector2 offset;

		Stopwatch shakeStopwatch;
	};

	class ShakeProxy : public ComponentProxy {
	public:
		ShakeProxy(Entity *entity, bool mustAddComponent = true);

		void shake(float newIntensity = 0.05f, double newDuration = 0.5,
		           bool forceReset = true, Shake::ShakeAxis newAxis = Shake::BOTH);
		
		const Vector2 &getOffset() const;
	};
}

#endif /* defined(BB_SHAKE_H) */

