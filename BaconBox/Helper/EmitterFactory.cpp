#include "EmitterFactory.h"

#include "BaconBox/EntityFactory.h"
#include "BaconBox/EmitterEntity.h"

#ifdef BB_FLASH_PLATFORM
#include <AS3/AS3.h>
#include <AS3/AS3++.h>
#include "BaconBox/Helper/Flash/FlashHelper.h"

#endif

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
		
		//BaconBox.EntityWrapper.EntityHolderMovieClip
		EmitterEntity *result = new EmitterEntity();
		
#if defined(BB_FLASH_PLATFORM)
//		AS3::local::var mc = FlashHelper::construct("BaconBox.EntityWrapper.EntityHolderMovieClip");
		AS3::local::var mc = FlashHelper::getMCFromMCEntity(result);
		//EmitterEntity *result = NULL;
		AS3::local::internal::trace(mc);
#endif
		
		// We initialize the emitter's properties.
		result->setInfiniteEmission(true);
		result->setMinForce(minForce);
		result->setMaxForce(maxForce);
		result->setMinAngle(minAngle);
		result->setMaxAngle(maxAngle);
		
		// We initialize the phases.
		
		// We initialize the main phase.
		ParticlePhase phaseOne;
		
		phaseOne.phaseDuration = particleLifespan;
		phaseOne.phaseDurationVariance = particleLifespanVariance;
		phaseOne.anglePerSecond = angularVelocity;
		phaseOne.anglePerSecondVariance = angularVelocityVariance;
		
		// We initialize the fade-out phase.
		ParticlePhase phaseTwo;

		phaseTwo.alphaPerSecond = -4.0f;
		phaseTwo.phaseDuration = particleLifespan;
		phaseTwo.phaseDurationVariance = particleLifespanVariance;
		phaseTwo.anglePerSecond = angularVelocity;
		phaseTwo.anglePerSecondVariance = angularVelocityVariance;
		
		result->getPhases().push_back(phaseOne);
		result->getPhases().push_back(phaseTwo);

		// We initialize the particles.
		result->getParticles().resize(nbParticles);

		for (Emitter::ParticleVector::iterator i = result->getParticles().begin(); i != result->getParticles().end(); ++i) {
			// We initialize the particle's graphic.
			i->second.graphic = EntityFactory::getMovieClipEntity(key);
			i->second.graphic->setAlphaMultiplier(0.0f);
			result->addChild(i->second.graphic);
			i->first = result->getPhases().end();
		}

		return result;
	}
}
