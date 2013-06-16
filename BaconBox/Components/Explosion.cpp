#include "BaconBox/Components/Explosion.h"

#include "BaconBox/Helper/Random.h"

namespace BaconBox {
	BB_ID_IMPL(Explosion);
	
	Explosion::Explosion() : Component(), Emitter(), minNbParticlesToShoot(10), maxNbParticlesToShoot(15) {
	}
	
	Explosion::Explosion(const Explosion &src) : Component(src), Emitter(src), minNbParticlesToShoot(src.minNbParticlesToShoot), maxNbParticlesToShoot(src.maxNbParticlesToShoot) {
	}
	
	Explosion::~Explosion() {
	}
	
	Explosion &Explosion::operator=(const Explosion &src) {
		this->Component::operator=(src);
		this->Emitter::operator=(src);
		
		if (this != &src) {
			this->minNbParticlesToShoot = src.minNbParticlesToShoot;
			this->maxNbParticlesToShoot = src.maxNbParticlesToShoot;
		}
		
		return *this;
	}
	
	Explosion *Explosion::clone() const {
		return new Explosion(*this);
	}
	
	void Explosion::explode() {
		int nbParticlesToShoot = Random::getRandomInteger(this->minNbParticlesToShoot, this->maxNbParticlesToShoot);
		
		for (int i = 0; i < nbParticlesToShoot; ++i) {
			this->emitParticle();
		}
	}
}
