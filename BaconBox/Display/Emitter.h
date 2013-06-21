#ifndef BB_EMITTER_H
#define BB_EMITTER_H

#include <list>
#include <vector>
#include <utility>
#include "BaconBox/Display/Particle.h"
#include "BaconBox/Display/ParticlePhase.h"

namespace BaconBox {
	class MovieClipEntity;

	/**
	 * Base class for particle emitters.
	 */
	class Emitter {
	public:
		/// Represents the type that contains the phases.
		typedef std::list<ParticlePhase> PhaseList;
		
		typedef std::vector<std::pair<PhaseList::const_iterator, Particle<MovieClipEntity> > > ParticleVector;

		Emitter();

		Emitter(const Emitter &src);

		virtual ~Emitter();

		Emitter &operator=(const Emitter &src);

		float getMinForce() const;
		void setMinForce(float newMinForce);

		float getMaxForce() const;
		void setMaxForce(float newMaxForce);

		float getMinAngle() const;
		void setMinAngle(float newMinAngle);

		float getMaxAngle() const;
		void setMaxAngle(float newMaxAngle);
		
		PhaseList &getPhases();
		
		const PhaseList &getPhases() const;
		
		ParticleVector &getParticles();
		
		const ParticleVector &getParticles() const;

		bool emitParticle();
	protected:
		virtual void initializeParticle(ParticleVector::iterator particle);
		
		void updateParticles();
	private:
		
		void updateParticle(ParticleVector::iterator particle);
		
		ParticleVector::iterator findFirstDeadParticle();
		
		void clearParticles();
		
		void startPhase(ParticleVector::iterator particle);
		
		ParticleVector particles;

		/**
		 * Minimum force applied to the particle when spawned.
		 */
		float minForce;

		/**
		 * Maximum force applied to the particle when spawned.
		 */
		float maxForce;

		/**
		 * Minimum angle at which each particle is spawned. The angle is between
		 * -180 and 180. Angle increases as it goes counter clockwise.
		 */
		float minAngle;

		/**
		 * Maximum angle at which each particle is spawned. The angle is between
		 * -180 and 180. Angle increases as it goes counter clockwise.
		 */
		float maxAngle;
		
		/**
		 * List of particle phases each particle go through before dying.
		 */
		PhaseList phases;
	};
}

#endif /* defined(BB_EMITTER_H) */

