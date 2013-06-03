#ifndef BB_PARTICLE_EMITTER_H
#define BB_PARTICLE_EMITTER_H

#include "BaconBox/Display/Emitter/Emitter.h"

namespace BaconBox {
	class ParticleEmitter : public Emitter {
	public:
		ParticleEmitter();
		
		ParticleEmitter(const ParticleEmitter &src);
		
		virtual ~ParticleEmitter();
		
		ParticleEmitter &operator=(const ParticleEmitter &src);
	private:
		bool enabled;
	};
}

#endif /* defined(BB_PARTICLE_EMITTER_H) */

