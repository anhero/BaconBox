#include "BaconBox/Components/ParticleEmitter.h"

namespace BaconBox {
	BB_ID_IMPL(ParticleEmitter);
	
	ParticleEmitter::ParticleEmitter() : Component(), Emitter(), enabled(false) {
	}
	
	ParticleEmitter::ParticleEmitter(const ParticleEmitter &src) : Component(src), Emitter(src), enabled(src.enabled) {
	}
	
	ParticleEmitter::~ParticleEmitter() {
	}
	
	ParticleEmitter &ParticleEmitter::operator=(const ParticleEmitter &src) {
		this->Component::operator=(src);
		this->Emitter::operator=(src);
		
		if (this != &src) {
			this->enabled = src.enabled;
		}
		
		return *this;
	}
	
	ParticleEmitter *ParticleEmitter::clone() const {
		return new ParticleEmitter(*this);
	}
	
	void ParticleEmitter::update() {
		if (this->enabled) {
		}
	}
	
	void ParticleEmitter::emitParticle(double lifetime, float force, float angle, float angularVelocity, int rotationDirection) {
	}
}
