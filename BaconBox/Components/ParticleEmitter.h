#ifndef BB_PARTICLE_EMITTER_H
#define BB_PARTICLE_EMITTER_H

#include "BaconBox/Display/Emitter.h"
#include "BaconBox/Core/Component.h"
#include "BaconBox/Helper/Stopwatch.h"

namespace BaconBox {
	class Transform;
	
	/**
	 * Emits particles at a given rate for a given period of time. Can be used
	 * to emit particles infinetly.
	 */
	class ParticleEmitter : public Component, public Emitter {
	public:
		BB_ID_HEADER;
		
		ParticleEmitter();
		
		ParticleEmitter(const ParticleEmitter &src);
		
		virtual ~ParticleEmitter();
		
		ParticleEmitter &operator=(const ParticleEmitter &src);
		
		virtual ParticleEmitter *clone() const;
		
		virtual void update();
		
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
		
		double getCurrentLifetime() const;
		
		double getEmissionRate() const;
		void setEmissionRate(double newEmissionRate);
		
	protected:
		void initializeParticle(ParticleVector::iterator particle);
		
	private:
		void initializeConnections();
		
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
		
		/**
		 * Lifetime the emitter currently has from the start() to the
		 * automatically called stop(). 0.0 if infiniteEmission is set to false
		 * or if the emitter is not currently emitting.
		 */
		double currentLifetime;

		/**
		 * Stopwatch used to keep track of when the emitter needs to stop.
		 */
		Stopwatch stopwatch;
		
		/// Number of particles spawned per second.
		double emissionRate;
		
		/**
		 * Stopwatch used to keep track of the time elapsed since the last time
		 * the update() was called. Only active when the emitter is currently
		 * emitting.
		 */
		Stopwatch updateStopwatch;
		
		/**
		 * Used to count the time to know when to emit particles.
		 */
		double timeCounter;
		
		Transform *transform;
	};
}

#endif /* defined(BB_PARTICLE_EMITTER_H) */

