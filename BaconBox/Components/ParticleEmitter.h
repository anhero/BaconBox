#ifndef BB_PARTICLE_EMITTER_H
#define BB_PARTICLE_EMITTER_H

#include "BaconBox/Display/Emitter.h"
#include "BaconBox/Core/Component.h"

namespace BaconBox {
	class ParticleEmitter : public Component, public Emitter {
	public:
		BB_ID_HEADER;
		
		ParticleEmitter();
		
		ParticleEmitter(const ParticleEmitter &src);
		
		virtual ~ParticleEmitter();
		
		ParticleEmitter &operator=(const ParticleEmitter &src);
		
		virtual ParticleEmitter *clone() const;
		
		virtual void update();
		
		using Emitter::emitParticle;
		
	protected:
		void emitParticle(double lifetime, float force, float angle, float angularVelocity, int rotationDirection);
	private:
		bool enabled;
	};
}

#endif /* defined(BB_PARTICLE_EMITTER_H) */

