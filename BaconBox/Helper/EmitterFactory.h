#ifndef BB_EMITTER_FACTORY_H
#define BB_EMITTER_FACTORY_H

#include <string>
#include "BaconBox/Vector2.h"

namespace BaconBox {
	class EmitterEntity;

	class EmitterFactory {
	public:
		static EmitterEntity *getEmitter(const std::string &key,
		                                 size_t nbParticles = 10,
		                                 float minForce = 40.0f, float maxForce = 60.0f,
		                                 float minAngle = -180.0f, float maxAngle = 180.0f,
		                                 double particleLifespan = 0.5,
		                                 double particleLifespanVariance = 0.75,
		                                 float angularVelocity = 0.0f,
										 float angularVelocityVariance = 0.0f,
		                                 const Vector2 &gravity = Vector2());
	};
}

#endif /* defined(BB_EMITTER_FACTORY_H) */

