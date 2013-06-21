#ifndef BB_SPEED_H
#define BB_SPEED_H

#include "BaconBox/Core/Component.h"
#include "BaconBox/Vector2.h"
#include "BaconBox/Helper/Stopwatch.h"

namespace BaconBox {
	class Transform;

	class Speed : public Component {
	public:
		BB_ID_HEADER;

		Speed();

		Speed(const Speed &src);

		virtual ~Speed();

		Speed &operator=(const Speed &src);

		virtual Speed *clone() const;

		virtual void receiveMessage(int senderID, int destID, int message, void *data);

		void update();

		const Vector2 &getVelocity() const;
		void setVelocity(const Vector2 &newVelocity);
		void setXVelocity(float newXVelocity);
		void setYVelocity(float newYVelocity);

		const Vector2 &getAcceleration() const;
		void setAcceleration(const Vector2 &newAcceleration);
		void setXAcceleration(float newXAcceleration);
		void setYAcceleration(float newYAcceleration);

		float getAngularVelocity() const;
		void setAngularVelocity(float newAngularVelocity);
	private:
		void initializeConnections();

		Vector2 velocity;
		Vector2 acceleration;
		float angularVelocity;

		Stopwatch updateStopwatch;

		Transform *transform;
	};

	class SpeedProxy : public ComponentProxy {
	public:
		SpeedProxy(Entity *entity, bool mustAddComponent = true);

		const Vector2 &getVelocity() const;
		void setVelocity(const Vector2 &newVelocity);
		void setXVelocity(float newXVelocity);
		void setYVelocity(float newYVelocity);

		const Vector2 &getAcceleration() const;
		void setAcceleration(const Vector2 &newAcceleration);
		void setXAcceleration(float newXAcceleration);
		void setYAcceleration(float newYAcceleration);

		float getAngularVelocity() const;
		void setAngularVelocity(float newAngularVelocity);
	};
}

#endif /* defined(BB_SPEED_H) */

