#include "BaconBox/Components/ParticleEmitter.h"

#include "BaconBox/Helper/Random.h"
#include "BaconBox/MovieClipEntity/MovieClipEntity.h"
#include "BaconBox/Components/Transform.h"
#include "BaconBox/Components/ComponentConnection.h"

namespace BaconBox {
	BB_ID_IMPL(ParticleEmitter);
	
	ParticleEmitter::ParticleEmitter() : Component(), Emitter(), infiniteEmission(true), minEmissionTime(0.0), maxEmissionTime(0.0), currentLifetime(0.0), stopwatch(), emissionRate(10.0), updateStopwatch(), timeCounter(0.0) {
		this->initializeConnections();
	}
	
	ParticleEmitter::ParticleEmitter(const ParticleEmitter &src) : Component(src), Emitter(src), infiniteEmission(src.infiniteEmission), minEmissionTime(src.minEmissionTime), maxEmissionTime(src.maxEmissionTime), currentLifetime(src.currentLifetime), stopwatch(src.stopwatch), emissionRate(src.emissionRate), updateStopwatch(src.updateStopwatch), timeCounter(src.timeCounter) {
		this->initializeConnections();
	}
	
	ParticleEmitter::~ParticleEmitter() {
	}
	
	ParticleEmitter &ParticleEmitter::operator=(const ParticleEmitter &src) {
		this->Component::operator=(src);
		this->Emitter::operator=(src);
		
		if (this != &src) {
			this->infiniteEmission = src.infiniteEmission;
			this->minEmissionTime = src.minEmissionTime;
			this->maxEmissionTime = src.maxEmissionTime;
			this->currentLifetime = src.currentLifetime;
			this->stopwatch = src.stopwatch;
			this->emissionRate = src.emissionRate;
			this->updateStopwatch = src.updateStopwatch;
			this->timeCounter = src.timeCounter;
		}
		
		return *this;
	}
	
	ParticleEmitter *ParticleEmitter::clone() const {
		return new ParticleEmitter(*this);
	}
	
	void ParticleEmitter::update() {
		this->Component::update();
		
		// We check if the particle emitter is active.
		if (this->updateStopwatch.isStarted()) {
			// We update the time counter used to count the particles to emit.
			this->timeCounter += this->updateStopwatch.getTime();

			// We check if we might have to stop the emitter.
			if (!this->isInfiniteEmission()) {
				// We get the time elapsed since the emitter started emitting.
				double elapsedSinceStart = this->stopwatch.getTime();
				
				// We check if it's done.
				if ( elapsedSinceStart > this->currentLifetime) {
					// We make sure to remove the overtime from the time counter.
					this->timeCounter -= this->currentLifetime - elapsedSinceStart;
					
					// We stop the particle emitter because its emission time is
					// over.
					this->stop();
				}
			}
			
			// We determine the number of particles to emit using the emission
			// rate.
			if (this->emissionRate > 0.0) {
				while (this->timeCounter > 1.0 / this->emissionRate) {
					this->emitParticle();
					
					this->timeCounter -= 1.0 / this->emissionRate;
				}
			}
			
			// If the emitter's emission time isn't done, we re-start the
			// stopwatch that we use to measure the time between updates.
			if (this->isEmitting()) {
				this->updateStopwatch.stop();
				this->updateStopwatch.start();
			}
		}
		
		this->updateParticles();
	}
	
	bool ParticleEmitter::isEmitting() const {
		return this->updateStopwatch.isStarted();
	}
	
	void ParticleEmitter::start() {
		this->updateStopwatch.start();
		
		if (!this->isInfiniteEmission()) {
			this->currentLifetime = Random::getRandomDouble(this->minEmissionTime, this->maxEmissionTime);
			this->stopwatch.start();
		}
	}
	
	void ParticleEmitter::pause() {
		this->updateStopwatch.pause();
		
		if (!this->isInfiniteEmission()) {
			this->stopwatch.pause();
		}
	}
	
	void ParticleEmitter::stop() {
		this->updateStopwatch.stop();
		
		if (!this->isInfiniteEmission()) {
			this->stopwatch.stop();
			this->currentLifetime = 0.0;
		}
	}
	
	void ParticleEmitter::explode() {
		while (this->emitParticle());
	}
	
	bool ParticleEmitter::isInfiniteEmission() const {
		return this->infiniteEmission;
	}
	
	void ParticleEmitter::setInfiniteEmission(bool newInfiniteEmission) {
		if (this->infiniteEmission != newInfiniteEmission) {
			this->infiniteEmission = newInfiniteEmission;
			
			if (this->infiniteEmission) {
				this->stopwatch.stop();
				this->currentLifetime = 0.0;
			} else if (this->isEmitting()) {
				this->stopwatch.start();
			}
		}
	}
	
	double ParticleEmitter::getMinEmissionTime() const {
		return this->minEmissionTime;
	}
	
	void ParticleEmitter::setMinEmissionTime(double newMinEmissionTime) {
		this->minEmissionTime = newMinEmissionTime;
	}
	
	double ParticleEmitter::getMaxEmissionTime() const {
		return this->maxEmissionTime;
	}
	
	void ParticleEmitter::setMaxEmissionTime(double newMaxEmissionTime) {
		this->maxEmissionTime = newMaxEmissionTime;
	}

	double ParticleEmitter::getCurrentLifetime() const {
		return this->currentLifetime;
	}

	double ParticleEmitter::getEmissionRate() const {
		return this->emissionRate;
	}
	
	void ParticleEmitter::setEmissionRate(double newEmissionRate) {
		this->emissionRate = newEmissionRate;
	}
	
	void ParticleEmitter::initializeParticle(ParticleVector::iterator particle) {
		this->Emitter::initializeParticle(particle);
		
		if (this->transform) {
			Transform *particleTransform = particle->second.graphic->getComponent<Transform>();
			
			if (particleTransform) {
				particleTransform->setPosition(this->transform->getPosition());
				particleTransform->setRotation(this->transform->getRotation());
				particleTransform->setScale(this->transform->getScale());
			}
			
			ColorTransform *particleColor = particle->second.graphic->getComponent<ColorTransform>();
			
			if (particleColor) {
				particleColor->setAlphaMultiplier(1.0);
			}
		}
	}
	
	void ParticleEmitter::initializeConnections() {
		this->addConnection(new ComponentConnection<Transform>(&this->transform));
		this->refreshConnections();
	}

	ParticleEmitterProxy::ParticleEmitterProxy(Entity *entity, bool mustAddComponent) : BB_PROXY_CONSTRUCTOR(new ParticleEmitter()) {
	}
	
	float ParticleEmitterProxy::getMinForce() const {
		return reinterpret_cast<ParticleEmitter *>(this->component)->getMinForce();
	}
	
	void ParticleEmitterProxy::setMinForce(float newMinForce) {
		reinterpret_cast<ParticleEmitter *>(this->component)->setMinForce(newMinForce);
	}
	
	float ParticleEmitterProxy::getMaxForce() const {
		return reinterpret_cast<ParticleEmitter *>(this->component)->getMaxForce();
	}
	
	void ParticleEmitterProxy::setMaxForce(float newMaxForce) {
		reinterpret_cast<ParticleEmitter *>(this->component)->setMaxForce(newMaxForce);
	}
	
	float ParticleEmitterProxy::getMinAngle() const {
		return reinterpret_cast<ParticleEmitter *>(this->component)->getMinAngle();
	}
	
	void ParticleEmitterProxy::setMinAngle(float newMinAngle) {
		reinterpret_cast<ParticleEmitter *>(this->component)->setMinAngle(newMinAngle);
	}
	
	float ParticleEmitterProxy::getMaxAngle() const {
		return reinterpret_cast<ParticleEmitter *>(this->component)->getMaxAngle();
	}
	
	void ParticleEmitterProxy::setMaxAngle(float newMaxAngle) {
		reinterpret_cast<ParticleEmitter *>(this->component)->setMaxForce(newMaxAngle);
	}
	
	Emitter::PhaseList &ParticleEmitterProxy::getPhases() {
		return reinterpret_cast<ParticleEmitter *>(this->component)->getPhases();
	}
	
	const Emitter::PhaseList &ParticleEmitterProxy::getPhases() const {
		return reinterpret_cast<ParticleEmitter *>(this->component)->getPhases();
	}
	
	Emitter::ParticleVector &ParticleEmitterProxy::getParticles() {
		return reinterpret_cast<ParticleEmitter *>(this->component)->getParticles();
	}
	
	const Emitter::ParticleVector &ParticleEmitterProxy::getParticles() const {
		return reinterpret_cast<ParticleEmitter *>(this->component)->getParticles();
	}
	
	bool ParticleEmitterProxy::emitParticle() {
		return reinterpret_cast<ParticleEmitter *>(this->component)->emitParticle();
	}

	
	bool ParticleEmitterProxy::isEmitting() const {
		return reinterpret_cast<ParticleEmitter *>(this->component)->isEmitting();
	}
	
	void ParticleEmitterProxy::start() {
		reinterpret_cast<ParticleEmitter *>(this->component)->start();
	}
	
	void ParticleEmitterProxy::pause() {
		reinterpret_cast<ParticleEmitter *>(this->component)->pause();
	}
	
	void ParticleEmitterProxy::stop() {
		reinterpret_cast<ParticleEmitter *>(this->component)->stop();
	}
	
	void ParticleEmitterProxy::explode() {
		reinterpret_cast<ParticleEmitter *>(this->component)->explode();
	}
	
	bool ParticleEmitterProxy::isInfiniteEmission() const {
		return reinterpret_cast<ParticleEmitter *>(this->component)->isInfiniteEmission();
	}
	
	void ParticleEmitterProxy::setInfiniteEmission(bool newInfiniteEmission) {
		reinterpret_cast<ParticleEmitter *>(this->component)->setInfiniteEmission(newInfiniteEmission);
	}
	
	double ParticleEmitterProxy::getMinEmissionTime() const {
		return reinterpret_cast<ParticleEmitter *>(this->component)->getMinEmissionTime();
	}
	
	void ParticleEmitterProxy::setMinEmissionTime(double newMinEmissionTime) {
		reinterpret_cast<ParticleEmitter *>(this->component)->setMinEmissionTime(newMinEmissionTime);
	}
	
	double ParticleEmitterProxy::getMaxEmissionTime() const {
		return reinterpret_cast<ParticleEmitter *>(this->component)->getMaxEmissionTime();
	}
	
	void ParticleEmitterProxy::setMaxEmissionTime(double newMaxEmissionTime) {
		reinterpret_cast<ParticleEmitter *>(this->component)->setMaxEmissionTime(newMaxEmissionTime);
	}
	
	double ParticleEmitterProxy::getCurrentLifetime() const {
		return reinterpret_cast<ParticleEmitter *>(this->component)->getCurrentLifetime();
	}
	
	double ParticleEmitterProxy::getEmissionRate() const {
		return reinterpret_cast<ParticleEmitter *>(this->component)->getEmissionRate();
	}
	
	void ParticleEmitterProxy::setEmissionRate(double newEmissionRate) {
		reinterpret_cast<ParticleEmitter *>(this->component)->setEmissionRate(newEmissionRate);
	}
}
