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
		
		virtual void update();
		
		void explode();
	private:
		/**
		 * The minimum number of particles that will be spawned every explosion.
		 */
		unsigned int minEmission;
		
		/**
		 * The maximum number of particles that will be spawned every explosion.
		 */
		unsigned int maxEmission;
	};
}

#endif /* defined(BB_EXPLOSION_H) */

