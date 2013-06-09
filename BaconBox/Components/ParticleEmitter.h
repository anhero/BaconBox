#ifndef BB_PARTICLE_EMITTER_H
#define BB_PARTICLE_EMITTER_H

#include "BaconBox/Display/Emitter.h"
#include "BaconBox/Core/Component.h"
#include "BaconBox/Helper/Stopwatch.h"

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
		
		bool isEmitting() const;
		
		void start();
		void pause();
		void stop();
		
		bool isInfiniteEmission() const;
		void setInfiniteEmission(bool newInfiniteEmission);
		
		double getMinEmissionTime() const;
		void setMinEmissionTime(double newMinEmissionTime);
		
		double getMaxEmissionTime() const;
		void setMaxEmissionTime(double newMaxEmissionTime);
		
		double getEmissionRate() const;
		void setEmissionRate(double newEmissionRate);
		
	protected:
		void emitParticle(double lifetime, float force, float angle, float angularVelocity, int rotationDirection);
	private:
		bool emitting;
		
		/**
		 * Determines whether or not the emitter emits particles infinitely
		 * when started.
		 */
		bool infiniteEmission;
		
		/**
		 * Minimum number of seconds the emitter will emit particles before
		 * stopping. Ignored if infiniteEmission is set to true.
		 */
		double minEmissionTime;
		/**
		 * Maximum number of seconds the emitter will emit particles before
		 * stopping. Ignored if infiniteEmission is set to true.
		 */
		double maxEmissionTime;

		Stopwatch stopwatch;
		
		/// Number of particles spawned per second.
		double emissionRate;
	};
}

#endif /* defined(BB_PARTICLE_EMITTER_H) */

