#include "Explosion.h"

namespace BaconBox {
	Explosion::Explosion() : Emitter(), minEmission(10), maxEmission(15) {
	}
	
	Explosion::Explosion(const Explosion &src) : Emitter(src), minEmission(src.minEmission), maxEmission(src.maxEmission) {
	}
	
	Explosion::~Explosion() {
	}
	
	Explosion &Explosion::operator=(const Explosion &src) {
		this->Emitter::operator=(src);
		
		if (this != &src) {
			this->minEmission = src.minEmission;
			this->maxEmission = src.maxEmission;
		}
		
		return *this;
	}
	
	void Explosion::explode() {
	}
}
