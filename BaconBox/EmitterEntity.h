#ifndef BB_EMITTER_ENTITY_H
#define BB_EMITTER_ENTITY_H

#include "BaconBox/MovieClipEntity/MovieClipEntity.h"
#include "BaconBox/Components/ParticleEmitter.h"

namespace BaconBox {
	class EmitterEntity : public MovieClipEntity, public ParticleEmitterProxy {
	public:
		EmitterEntity();
		
		EmitterEntity(const EmitterEntity &src);
		
		virtual ~EmitterEntity();
		
		EmitterEntity &operator=(const EmitterEntity &src);
	private:
	};
}

#endif /* defined(BB_EMITTER_ENTITY_H) */

