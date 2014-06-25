#ifndef BB_PARTICLE_COMPONENT_H
#define BB_PARTICLE_COMPONENT_H

#include "BaconBox/Core/Component.h"
#include "BaconBox/Core/Entity.h"
#include "BaconBox/AABB.h"
#include "BaconBox/DIsplay/Color.h"

namespace BaconBox {
	
	class Transform;
	class Visibility;
	class Speed;
	class ColorTransform;
//	class Color;
//	class AABB;
	
	struct ParicleInitInfo{};
	
	class ParticleComponent : public Component {
		friend class ParticleEmitterComponent;
	public:
		BB_ID_HEADER;
		
		ParticleComponent();
		
	
		virtual void standby()=0;


		virtual void initParticle()=0;
		
		virtual void updateParticle(float completionRatio, int updateCount, float time)=0;
		

	protected:
		void setPhases(std::vector<ParicleInitInfo*> & phases);
		std::vector<ParicleInitInfo*> * phases;
		enum {
			STANDBY,
			USED
		} status;
		
	private:
		
		

	};

	struct DefaultParicleInitInfo : public ParicleInitInfo{
		DefaultParicleInitInfo():skipPosition(false), reuseColorMultiplier(false), minStartScale(1.0f,1.0f), maxStartScale(0.0f,0.0f), minEndScale(1.0f,1.0f), maxEndScale(0.0f,0.0f), minSpeedLength(0.0f), maxSpeedLength(0.0f), minSpeedAngle(0.0f), maxSpeedAngle(0.0f), minAccelLength(0.0f), maxAccelLength(0.0f), minAccelAngle(0.0f), maxAccelAngle(0.0f), minUpdateLife(-1), maxUpdateLife(-1), minStartColorMultiplier(Color::WHITE), maxStartColorMultiplier(Color::NO_COLOR), minEndColorMultiplier(Color::WHITE), maxEndColorMultiplier(Color::NO_COLOR), keepScaleRatio(true), reuseScale(false), minAngularVelocity(0.0f), maxAngularVelocity(-1.0f){}
		AABB aabb;
		bool skipPosition;
		bool reuseScale;
		bool reuseColorMultiplier;
		bool keepScaleRatio;
		Vector2 minStartScale;
		Vector2 maxStartScale;
		Vector2 minEndScale;
		Vector2 maxEndScale;
		float minSpeedLength;
		float maxSpeedLength;
		float minSpeedAngle;
		float maxSpeedAngle;
		float minAccelLength;
		float maxAccelLength;
		float minAccelAngle;
		
		float minAngularVelocity;
		float maxAngularVelocity;
		
		float maxAccelAngle;
		int minUpdateLife;
		int maxUpdateLife;
		Color minStartColorMultiplier;
		Color maxStartColorMultiplier;
		Color minEndColorMultiplier;
		Color maxEndColorMultiplier;
		
	};
	


	class DefaultParticleComponent : public ParticleComponent {
	public:
		
		DefaultParticleComponent();
		virtual ~DefaultParticleComponent();
		
		void standby();

		void initParticle();
		
		void updateParticle(float completionRatio, int updateCount, float time);
		
		
	protected:
		
	private:
		int phasesIterator;
		int initialUpdateLife;
		int updateLife;
		Vector2 startScale;
		Vector2 endScale;
		Color startColorMultiplier;
		Color endColorMultiplier;
		
		void initializeConnections();
			Visibility *visibility;
			Transform *transform;
		Speed * speed;
		ColorTransform * colorTransform;
	};

}
#endif /* defined(BB_PARTICLE_EMITTER_H) */

