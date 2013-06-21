#include "EmitterEntity.h"

namespace BaconBox {
	EmitterEntity::EmitterEntity() : MovieClipEntity(), ParticleEmitterProxy(this) {
	}
	
	EmitterEntity::EmitterEntity(const EmitterEntity &src) : MovieClipEntity(src), ParticleEmitterProxy(this) {
	}
	
	EmitterEntity::~EmitterEntity() {
	}
	
	EmitterEntity &EmitterEntity::operator=(const EmitterEntity &src) {
		this->MovieClipEntity::operator=(src);
		
		if (this != &src) {
		}
		
		return *this;
	}
}
