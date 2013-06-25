#include "BaconBox/Display/Emitter.h"

#include "BaconBox/Helper/Random.h"
#include "BaconBox/Core/Engine.h"
#include "BaconBox/MovieClipEntity/MovieClipEntity.h"
#include "BaconBox/Components/Speed.h"

namespace BaconBox {
	Emitter::Emitter() : particles(), minForce(20.0), maxForce(40.0), minAngle(-180.0), maxAngle(180.0), phases(), updateStopwatch(){
	}

	Emitter::Emitter(const Emitter &src) : particles(src.particles), minForce(src.minForce), maxForce(src.maxForce), minAngle(src.minAngle), maxAngle(src.maxAngle), phases(src.phases), updateStopwatch(src.updateStopwatch) {
	}

	Emitter::~Emitter() {
	}

	Emitter &Emitter::operator=(const Emitter &src) {
		if (this != &src) {
			this->particles = src.particles;
			this->minForce = src.minForce;
			this->maxForce = src.maxForce;
			this->minAngle = src.minAngle;
			this->maxAngle = src.maxAngle;
			this->phases = src.phases;
			this->updateStopwatch = src.updateStopwatch;
		}

		return *this;
	}

	float Emitter::getMinForce() const {
		return this->minForce;
	}
	void Emitter::setMinForce(float newMinForce) {
		this->minForce = newMinForce;
	}

	float Emitter::getMaxForce() const {
		return this->maxForce;
	}
	void Emitter::setMaxForce(float newMaxForce) {
		this->maxForce = newMaxForce;
	}

	float Emitter::getMinAngle() const {
		return this->minAngle;
	}
	void Emitter::setMinAngle(float newMinAngle) {
		this->minAngle = newMinAngle;
	}

	float Emitter::getMaxAngle() const {
		return this->maxAngle;
	}
	void Emitter::setMaxAngle(float newMaxAngle) {
		this->maxAngle = newMaxAngle;
	}
	
	Emitter::PhaseList &Emitter::getPhases() {
		return this->phases;
	}
	
	const Emitter::PhaseList &Emitter::getPhases() const {
		return this->phases;
	}
	
	Emitter::ParticleVector &Emitter::getParticles() {
		return this->particles;
	}
	
	const Emitter::ParticleVector &Emitter::getParticles() const {
		return this->particles;		
	}

	bool Emitter::emitParticle() {
		bool result = false;
		
		// We try to get a dead particle.
		ParticleVector::iterator particle = this->findFirstDeadParticle();
		
		if (particle != this->particles.end()) {
			// We make sure the particle has a valid graphic.
			if (particle->second.graphic) {
				// We initialize the graphic's properties.
				this->initializeParticle(particle);
				
				// We set its first phase.
				particle->first = this->phases.begin();
				
				// We start the phase.
				this->startPhase(particle);
				
				// We check if the particle was correctly started.
				result = particle->second.timeLeft > 0.0;
			}
		}
		
		return result;
	}

	void Emitter::initializeParticle(ParticleVector::iterator particle) {
		float force = Random::getRandomFloat(this->minForce, this->maxForce);
		float angle = Random::getRandomFloat(this->minAngle, this->maxAngle);

		Speed *speed = reinterpret_cast<Speed *>(particle->second.graphic->getComponent(Speed::ID));
		
		if (speed) {
			Vector2 velocity(0.0f, force);
			velocity.rotate(angle);
			
			speed->setVelocity(velocity);
		}
		
		ColorTransform *particleColor = particle->second.graphic->getComponent<ColorTransform>();
		
		if (particleColor) {
			particleColor->setAlphaMultiplier(1.0);
		}
		
		particle->second.timeLeft = 0.0;
		particle->second.alphaCounter = 1.0f;
	}
	
	void Emitter::updateParticles() {
		// We update all particles.
		for (ParticleVector::iterator i = this->particles.begin(); i != this->particles.end(); ++i) {
			this->updateParticle(i);
		}
		
		this->updateStopwatch.stop();
		this->updateStopwatch.start();
	}
	
	void Emitter::updateParticle(ParticleVector::iterator particle) {
		// We check if the particle is still alive.
		if (particle->second.timeLeft > 0.0) {
			float timeElapsed = static_cast<float>(this->updateStopwatch.getTime());
			
			// We update the particle.
			
			// We update the particle's alpha.
			if (particle->second.alphaPerSecond != 0.0f) {
				particle->second.alphaCounter = std::min(particle->second.alphaCounter + timeElapsed * particle->second.alphaPerSecond, 1.0f);
				particle->second.graphic->setAlphaMultiplier(particle->second.alphaCounter);
			}
			
			// We update the particle's scaling, if needed.
			if (particle->second.scalingPerSecond != Vector2()) {
				particle->second.graphic->setScale(particle->second.graphic->getScale() + (particle->second.scalingPerSecond * timeElapsed));
			}
			
			// We update the particle's rotation, if needed.
			if (particle->second.anglePerSecond != 0.0f) {
				particle->second.graphic->setRotation(particle->second.graphic->getRotation() + (particle->second.anglePerSecond * timeElapsed));
			}
			
			// We update the particle's graphic.
#if defined(BB_FLASH_PLATFORM)
			particle->second.graphic->update();
#endif
			
			// We update the particle's life span.
			particle->second.timeLeft -= timeElapsed;
		}
		
		// We update the particle's phase.
		while (particle->second.timeLeft <= 0.0 && particle->first != this->getPhases().end()) {
			++(particle->first);
			
			if (particle->first != this->getPhases().end()) {
				this->startPhase(particle);
			}
		}
	}

	Emitter::ParticleVector::iterator Emitter::findFirstDeadParticle() {
		bool notFound = true;

		ParticleVector::iterator i = this->particles.begin();

		while (notFound && i != this->particles.end()) {
			if (i->second.timeLeft <= 0.0) {
				notFound = false;

			} else {
				++i;
			}
		}

		return i;
	}
	
	void Emitter::startPhase(ParticleVector::iterator particle) {
		// We make sure the phase is valid.
		if (particle->first != this->phases.end()) {
			particle->second.timeLeft = particle->first->phaseDuration + Random::getRandomDouble(0.0, particle->first->phaseDurationVariance);
			
			if (!particle->first->animationName.empty()) {
				particle->second.graphic->gotoAndPlay(particle->first->animationName);
			}
			
			particle->second.alphaCounter = 1.0f;
			particle->second.alphaPerSecond = particle->first->alphaPerSecond + Random::getRandomFloat(0.0f, particle->first->alphaPerSecondVariance);
			particle->second.scalingPerSecond = particle->first->scalingPerSecond + Vector2(Random::getRandomFloat(0.0f, particle->first->scalingPerSecondVariance.x), Random::getRandomFloat(0.0f, particle->first->scalingPerSecondVariance.y));
			particle->second.anglePerSecond = particle->first->anglePerSecond + Random::getRandomFloat(0.0f, particle->first->anglePerSecondVariance);
		}
	}
}
