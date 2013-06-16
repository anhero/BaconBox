#include "BaconBox/Display/Emitter.h"

#include "BaconBox/Helper/Random.h"
#include "BaconBox/MovieClipEntity/MovieClipEntity.h"
#include "BaconBox/Components/Transform.h"

namespace BaconBox {
	Emitter::Emitter() : particles(), minLifetime(0.2), maxLifetime(0.8), minForce(20.0), maxForce(40.0), minAngle(-180.0), maxAngle(180.0), phases() {
	}

	Emitter::Emitter(const Emitter &src) : particles(src.particles), minLifetime(src.minLifetime), maxLifetime(src.maxLifetime), minForce(src.minForce), maxForce(src.maxForce), minAngle(src.minAngle), maxAngle(src.maxAngle), phases(src.phases) {
	}

	Emitter::~Emitter() {
		this->clearParticles();
	}

	Emitter &Emitter::operator=(const Emitter &src) {
		if (this != &src) {
			this->particles = src.particles;
			this->minLifetime = src.minLifetime;
			this->maxLifetime = src.maxLifetime;
			this->minForce = src.minForce;
			this->maxForce = src.maxForce;
			this->minAngle = src.minAngle;
			this->maxAngle = src.maxAngle;
			this->phases = src.phases;
		}

		return *this;
	}

	double Emitter::getMinLifetime() const {
		return this->minLifetime;
	}
	void Emitter::setMinLifetime(double newMinLifetime) {
		this->minLifetime = newMinLifetime;
	}

	double Emitter::getMaxLifetime() const {
		return this->maxLifetime;
	}
	void Emitter::setMaxLifetime(double newMaxLifetime) {
		this->maxLifetime = newMaxLifetime;
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
		double lifetime = Random::getRandomDouble(this->minLifetime, this->maxLifetime);
		float force = Random::getRandomFloat(this->minForce, this->maxForce);
		float angle = Random::getRandomFloat(this->minAngle, this->maxAngle);
		
		particle->second.timeLeft = lifetime;
		
		Transform *transform = reinterpret_cast<Transform *>(particle->second.graphic->getComponent(Transform::ID));
		
		if (transform) {
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
	
	void Emitter::clearParticles() {
	}
	
	void Emitter::startPhase(ParticleVector::iterator particle) {
		// We make sure the phase is valid.
		if (particle->first != this->phases.end()) {
		}
	}
}
