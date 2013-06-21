#include "EmitterFactory.h"

#include "BaconBox/EntityFactory.h"
#include "BaconBox/EmitterEntity.h"

namespace BaconBox {
	EmitterEntity *EmitterFactory::getEmitter(const std::string &key,
	                                          size_t nbParticles,
	                                          float minForce, float maxForce,
	                                          float minAngle, float maxAngle,
	                                          double particleLifespan,
	                                          double particleLifespanVariance,
	                                          float angularVelocity,
											  float angularVelocityVariance,
	                                          const Vector2 &gravity) {
		EmitterEntity *result = new EmitterEntity();
		
		// We initialize the emitter's properties.
		result->setInfiniteEmission(true);
		result->setMinForce(minForce);
		result->setMaxForce(maxForce);
		result->setMinAngle(minAngle);
		result->setMaxAngle(maxAngle);
		
		// We initialize the phases.
		result->getPhases().resize(2);
		
		// We initialize the main phase.
		ParticlePhase &phaseOne = result->getPhases().front();
		
		phaseOne.phaseDuration = particleLifespan;
		phaseOne.phaseDurationVariance = particleLifespanVariance;
		phaseOne.anglePerSecond = angularVelocity;
		phaseOne.anglePerSecondVariance = angularVelocityVariance;
		
		// We initialize the fade-out phase.
		ParticlePhase &phaseTwo = result->getPhases().back();

		phaseTwo.alphaPerSecond = -4.0f;
		phaseTwo.phaseDuration = particleLifespan;
		phaseTwo.phaseDurationVariance = particleLifespanVariance;
		phaseTwo.anglePerSecond = angularVelocity;
		phaseTwo.anglePerSecondVariance = angularVelocityVariance;

		// We initialize the particles.
		result->getParticles().resize(nbParticles);

		for (Emitter::ParticleVector::iterator i = result->getParticles().begin(); i != result->getParticles().end(); ++i) {
			// We initialize the particle's graphic.
			i->second.graphic = EntityFactory::getMovieClipEntity(key);
		}

		return result;
	}
}
