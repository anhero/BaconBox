#ifndef BB_SHAKE_H
#define BB_SHAKE_H

#include "BaconBox/Core/Component.h"
#include "BaconBox/Helper/Stopwatch.h"
#include "BaconBox/Vector2.h"

namespace BaconBox {
	class Transform;
	
	class Shake : public Component {
	public:
		BB_ID_HEADER;
		
		Shake();
		
		Shake(const Shake &src);
		
		virtual ~Shake();
		
		Shake &operator=(const Shake &src);
		
		virtual Shake *clone() const;
		
		void update();

		void shake(double newDuration, float newIntensity);
	private:
		void initializeConnections();
		
		Transform *transform;
		
		float intensity;
		
		double duration;
		
		Vector2 initialPosition;
		
		Stopwatch shakeStopwatch;
	};
}

#endif /* defined(BB_SHAKE_H) */

