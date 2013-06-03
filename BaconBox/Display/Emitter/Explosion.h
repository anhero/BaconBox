#ifndef BB_EXPLOSION_H
#define BB_EXPLOSION_H

#include "BaconBox/Display/Emitter/Emitter.h"

namespace BaconBox {
	class Explosion : public Emitter {
	public:
		Explosion();
		
		Explosion(const Explosion &src);
		
		virtual ~Explosion();
		
		Explosion &operator=(const Explosion &src);
		
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

