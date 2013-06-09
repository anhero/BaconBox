#ifndef BB_EXPLOSION_H
#define BB_EXPLOSION_H

#include "BaconBox/Core/Component.h"
#include "BaconBox/Display/Emitter/Emitter.h"

namespace BaconBox {
	/**
	 * Represents a particle emitter that emits its particles all at the same
	 * time, like an explosion.
	 */
	class Explosion : public Component, public Emitter {
	public:
		BB_ID_HEADER;
		
		Explosion();
		
		Explosion(const Explosion &src);
		
		virtual ~Explosion();
		
		Explosion &operator=(const Explosion &src);
		
		virtual Explosion *clone() const;
		
		/**
		 * Makes the explosion emit all of its particles.
		 */
		void explode();
		
		int getMinNbParticlesToShoot() const;
		void setMinNbParticlesToShoot(int newMinNbParticlesToShoot);
		
		int getMaxNbParticlesToShoot() const;
		void setMaxNbParticlesToShoot(int newMaxNbParticlesToShoot);
		
		using Emitter::emitParticle;
		
	protected:
		void emitParticle(double lifetime, float force, float angle, float angularVelocity, int rotationDirection);
	private:
		/**
		 * The minimum number of particles that will be spawned every explosion.
		 */
		int minNbParticlesToShoot;
		
		/**
		 * The maximum number of particles that will be spawned every explosion.
		 */
		int maxNbParticlesToShoot;
	};
}

#endif /* defined(BB_EXPLOSION_H) */

