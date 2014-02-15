#ifndef BB_PARTICLE_EMITTER_H
#define BB_PARTICLE_EMITTER_H

#include "BaconBox/MovieClipEntity/MovieClipEntity.h"
#include "BaconBox/Components/ParticleEmitterComponent.h"
#include "BaconBox/EntityFactory.h"

namespace BaconBox {
	class ParticleEmitter : public MovieClipEntity, public ParticleEmitterComponentProxy {
	public:
		ParticleEmitter();
		
		
		template <typename ParticleComponentClass>
		static ParticleEmitter * getParticleEmitter(const std::string & key, int nbParticle, MovieClipEntity * parent = NULL)  {
			ParticleEmitter * particleEmitter = new ParticleEmitter();
			std::vector<MovieClipEntity*> mcs(nbParticle);
			for(int i = 0; i < nbParticle; i++){
				MovieClipEntity* mc = EntityFactory::getMovieClipEntity(key);
				mc->addComponent(new ParticleComponentClass());
				mcs[i] = mc;
			}
			particleEmitter->setParticles(mcs, parent);
			return particleEmitter;
		}
		virtual ~ParticleEmitter();
		
		
	private:
	};
}

#endif

