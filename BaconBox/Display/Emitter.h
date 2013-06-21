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

		double getMinLifetime() const;
		void setMinLifetime(double newMinLifetime);

		double getMaxLifetime() const;
		void setMaxLifetime(double newMaxLifetime);

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
	private:
		void initializeParticle(ParticleVector::iterator particle);
		
		ParticleVector::iterator findFirstDeadParticle();
		
		void clearParticles();
		
		void startPhase(ParticleVector::iterator particle);
		
		ParticleVector particles;
		
		/**
		 * The minimum lifetime of each particle, measured in seconds.
		 */
		double minLifetime;

		/**
		 * The maximum lifetime of each particle, measured in seconds.
		 */
		double maxLifetime;

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
		
		PhaseList phases;
	};
}

#endif /* defined(BB_EMITTER_H) */

