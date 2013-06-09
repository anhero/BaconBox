#include "BaconBox/Components/ParticleEmitter.h"

namespace BaconBox {
	BB_ID_IMPL(ParticleEmitter);
	
	ParticleEmitter::ParticleEmitter() : Component(), Emitter(), emitting(false), infiniteEmission(true), minEmissionTime(0.0), maxEmissionTime(0.0), stopwatch(), emissionRate(10.0) {
	}
	
	ParticleEmitter::ParticleEmitter(const ParticleEmitter &src) : Component(src), Emitter(src), emitting(src.emitting), infiniteEmission(src.infiniteEmission), minEmissionTime(src.minEmissionTime), maxEmissionTime(src.maxEmissionTime), stopwatch(src.stopwatch), emissionRate(src.emissionRate) {
	}
	
	ParticleEmitter::~ParticleEmitter() {
	}
	
	ParticleEmitter &ParticleEmitter::operator=(const ParticleEmitter &src) {
		this->Component::operator=(src);
		this->Emitter::operator=(src);
		
		if (this != &src) {
			this->emitting = src.emitting;
			this->infiniteEmission = src.infiniteEmission;
			this->minEmissionTime = src.minEmissionTime;
			this->maxEmissionTime = src.maxEmissionTime;
			this->stopwatch = src.stopwatch;
			this->emissionRate = src.emissionRate;
		}
		
		return *this;
	}
	
	ParticleEmitter *ParticleEmitter::clone() const {
		return new ParticleEmitter(*this);
	}
	
	void ParticleEmitter::update() {
		if (this->emitting) {
		}
	}
	
	bool ParticleEmitter::isEmitting() const {
		return this->emitting;
	}
	
	void ParticleEmitter::start() {
		this->emitting = true;
		
		if (!this->isInfiniteEmission()) {
			this->stopwatch.start();
		}
	}
	
	void ParticleEmitter::pause() {
		this->emitting = false;
		
		if (!this->isInfiniteEmission()) {
			this->stopwatch.pause();
		}
	}
	
	void ParticleEmitter::stop() {
		this->emitting = false;
		
		if (!this->isInfiniteEmission()) {
			this->stopwatch.stop();
		}
	}
	
	bool ParticleEmitter::isInfiniteEmission() const {
		return this->infiniteEmission;
	}
	
	void ParticleEmitter::setInfiniteEmission(bool newInfiniteEmission) {
		if (this->infiniteEmission != newInfiniteEmission) {
			this->infiniteEmission = newInfiniteEmission;
			
			if (this->infiniteEmission) {
				this->stopwatch.stop();
			} else if (this->emitting) {
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
	
	double ParticleEmitter::getEmissionRate() const {
		return this->emissionRate;
	}
	
	void ParticleEmitter::setEmissionRate(double newEmissionRate) {
		this->emissionRate = newEmissionRate;
	}
	
	void ParticleEmitter::emitParticle(double lifetime, float force, float angle, float angularVelocity, int rotationDirection) {
	}
}
