#ifndef BB_PARTICLE_EMITTER_COMPONENT_H
#define BB_PARTICLE_EMITTER_COMPONENT_H

#include "BaconBox/Core/Component.h"


namespace BaconBox {
	class Transform;
	class ParticleComponent;
	class MovieClipEntity;
	class ParicleInitInfo;
	/**
	 * Emits particles at a given rate for a given period of time. Can be used
	 * to emit particles infinetly.
	 */
	class ParticleEmitterComponent : public Component{
	public:
		BB_ID_HEADER;
		
		ParticleEmitterComponent();
		
		void setParticles(std::vector<MovieClipEntity*> & mcs, MovieClipEntity * parent = NULL);
		
		virtual ~ParticleEmitterComponent();
		
		void start();
		void stop();
		
		void setUpdateCycle(int minUpdate, int maxUpdate = -1);
		void setNbEmited(int minEmited, int maxEmited = -1);
		void update();
		void emit();
		void reset();
		void addPhase(ParicleInitInfo * initializationData);
	protected:
		int minEmited;
		int maxEmited;
		int updateCount;
		float completionRatio;
		std::vector<ParicleInitInfo*> phases;
		bool isOn;
		enum{
			UPDATE,
			TIME,
			NONE,
		} emitCycle;
		union{
			struct{
				int nbOfEmited;
				int minUpdate;
				int maxUpdate;
				int updateIncr;
				int nextUpdate;
			} updateParams;
		} cycleParams;
		
	private:
		
		std::vector<ParticleComponent*> particles;
		void initializeConnections();

		Transform *transform;
	};
	
	class ParticleEmitterComponentProxy : public ComponentProxy {
	public:
		ParticleEmitterComponentProxy(Entity *entity, bool mustAddComponent = true);
		void setParticles(std::vector<MovieClipEntity*> & mcs, MovieClipEntity * parent = NULL);
		
		void start();
		void stop();
		void reset();
		
		void setUpdateCycle(int minUpdate, int maxUpdate = -1);
		void setNbEmited(int minEmited, int maxEmited = -1);
		void update();
		void emit();
		void addPhase(ParicleInitInfo * initializationData);
		
	};
}

#endif /* defined(BB_PARTICLE_EMITTER_H) */

