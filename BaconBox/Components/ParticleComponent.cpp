
#include "ParticleComponent.h"

#include "BaconBox/MovieClipEntity/MovieClipEntity.h"
#include "BaconBox/Components/ComponentConnection.h"
#include "BaconBox/Components/Transform.h"
#include "BaconBox/Components/Speed.h"
#include "BaconBox/Components/ColorTransform.h"


#include "BaconBox/Helper/Random.h"
#include "BaconBox/AABB.h"
#include "BaconBox/Console.h"
using namespace BaconBox;

	BB_ID_IMPL(ParticleComponent);

ParticleComponent::ParticleComponent():Component(){}
void ParticleComponent::setPhases(std::vector<ParicleInitInfo*> & phases){
	this->phases = &phases;
}

DefaultParticleComponent::~DefaultParticleComponent(){
}


DefaultParticleComponent::DefaultParticleComponent():ParticleComponent(), phasesIterator(0), speed(NULL), colorTransform(NULL), transform(NULL), visibility(NULL){
	this->initializeConnections();
}


void DefaultParticleComponent::standby(){
	visibility->setVisible(false);
	status = STANDBY;
	phasesIterator = 0;
}

void DefaultParticleComponent::initParticle(){
	visibility->setVisible(true);
	status = USED;
	DefaultParicleInitInfo * data = (DefaultParicleInitInfo*)(*phases)[phasesIterator];
	if (!data->skipPosition) {
	AABB & aabb = data->aabb;
	transform->setPosition(Vector2(Random::getRandomFloat(aabb.getLeft(), aabb.getRight()), Random::getRandomFloat(aabb.getTop(), aabb.getBottom())));
	}
	float minSpeedLength = data->minSpeedLength;
	float maxSpeedLength = data->maxSpeedLength;
	float minSpeedAngle = data->minSpeedAngle;
	float maxSpeedAngle = data->maxSpeedAngle;
	
	
	float minAccelLength = data->minAccelLength;
	float maxAccelLength = data->maxAccelLength;
	float minAccelAngle = data->minAccelAngle;
	float maxAccelAngle = data->maxAccelAngle;
	
	
	int minUpdateLife = data->minUpdateLife;
	int maxUpdateLife = data->maxUpdateLife;
	
	
	float minStartAngle = data->minStartAngle;
	float maxStartAngle = data->maxStartAngle;
	
    
    float minAngularVelocity = data->minAngularVelocity;
	float maxAngularVelocity = data->maxAngularVelocity;
    
    if (maxStartAngle < minStartAngle)maxStartAngle = minStartAngle;

	if (maxAngularVelocity < minAngularVelocity)maxAngularVelocity = minAngularVelocity;

	
	if (maxSpeedLength < minSpeedLength)maxSpeedLength = minSpeedLength;
	if (maxSpeedAngle < minSpeedAngle)maxSpeedAngle = minSpeedAngle;
	
	if (maxAccelLength < minAccelLength)maxAccelLength = minAccelLength;
	if (maxAccelAngle < minAccelAngle)maxAccelAngle = minAccelAngle;
	
	
	if (maxUpdateLife < minUpdateLife)maxUpdateLife = minUpdateLife;

	float speedLength = Random::getRandomFloat(minSpeedLength, maxSpeedLength);
	float speedAngle = Random::getRandomFloat(minSpeedAngle, maxSpeedAngle);
	
	float accelLength = Random::getRandomFloat(minAccelLength, maxAccelLength);
	float accelAngle = Random::getRandomFloat(minAccelAngle, maxAccelAngle);
	
    if (!data->skipRotation) {
        transform->setRotation(Random::getRandomFloat(minStartAngle, maxStartAngle));
    }

	speed->setAngularVelocity(Random::getRandomFloat(minAngularVelocity, maxAngularVelocity));
	
	updateLife = Random::getRandomInteger(minUpdateLife, maxUpdateLife);
	initialUpdateLife = updateLife;
	if(speedLength > 0 ){
		Vector2 velocity(1.0f, 1.0f);
		velocity.setLength(speedLength);
		velocity.setAngle(speedAngle);
		speed->setVelocity(velocity);
	}

	if(accelLength > 0){
		Vector2 accel(1.0f, 1.0f);
		accel.setLength(accelLength);
		accel.setAngle(accelAngle);
		speed->setAcceleration(accel);
	}

	
	Vector2 minStartScale = data->minStartScale;
	Vector2 maxStartScale = data->maxStartScale;
	if (maxStartScale == Vector2())maxStartScale = minStartScale;
	Vector2 minEndScale = data->minEndScale;
	Vector2 maxEndScale = data->maxEndScale;
	if (maxEndScale == Vector2())maxEndScale = minEndScale;

	if (data->reuseScale){
		startScale = endScale;
	}
	else{
		startScale = Random::getRandomVector2(minStartScale, maxStartScale, data->keepScaleRatio);
	}
	endScale = Random::getRandomVector2(minEndScale, maxEndScale, data->keepScaleRatio);
	transform->setScale(startScale);
	
	

	Color minStartColorMultiplier = data->minStartColorMultiplier;
	Color maxStartColorMultiplier = data->maxStartColorMultiplier;
	Color minEndColorMultiplier = data->minEndColorMultiplier;
	Color maxEndColorMultiplier = data->maxEndColorMultiplier;
	
	if(maxStartColorMultiplier.getRed() < minStartColorMultiplier.getRed()) maxStartColorMultiplier.setRed(minStartColorMultiplier.getRed());
	if(maxStartColorMultiplier.getGreen() < minStartColorMultiplier.getGreen()) maxStartColorMultiplier.setGreen(minStartColorMultiplier.getGreen());
	if(maxStartColorMultiplier.getBlue() < minStartColorMultiplier.getBlue()) maxStartColorMultiplier.setBlue(minStartColorMultiplier.getBlue());
	if(maxStartColorMultiplier.getAlpha() < minStartColorMultiplier.getAlpha()) maxStartColorMultiplier.setAlpha(minStartColorMultiplier.getAlpha());

	
	if(maxEndColorMultiplier.getRed() < minEndColorMultiplier.getRed()) maxEndColorMultiplier.setRed(minEndColorMultiplier.getRed());
	if(maxEndColorMultiplier.getGreen() < minEndColorMultiplier.getGreen()) maxEndColorMultiplier.setGreen(minEndColorMultiplier.getGreen());
	if(maxEndColorMultiplier.getBlue() < minEndColorMultiplier.getBlue()) maxEndColorMultiplier.setBlue(minEndColorMultiplier.getBlue());
	if(maxEndColorMultiplier.getAlpha() < minEndColorMultiplier.getAlpha()) maxEndColorMultiplier.setAlpha(minEndColorMultiplier.getAlpha());

	if (data->reuseColorMultiplier){
		startColorMultiplier = endColorMultiplier;
	}
	else{
	startColorMultiplier = Color(Random::getRandomFloat(minStartColorMultiplier.getRed(),maxStartColorMultiplier.getRed()),
								Random::getRandomFloat(minStartColorMultiplier.getGreen(),maxStartColorMultiplier.getGreen()),
								 Random::getRandomFloat(minStartColorMultiplier.getBlue(),maxStartColorMultiplier.getBlue()),
								 Random::getRandomFloat(minStartColorMultiplier.getAlpha(),maxStartColorMultiplier.getAlpha()));
	}
										 
	endColorMultiplier = Color(Random::getRandomFloat(minEndColorMultiplier.getRed(),maxEndColorMultiplier.getRed()),
							   Random::getRandomFloat(minEndColorMultiplier.getGreen(),maxEndColorMultiplier.getGreen()),
							  Random::getRandomFloat(minEndColorMultiplier.getBlue(),maxEndColorMultiplier.getBlue()),
							  Random::getRandomFloat(minEndColorMultiplier.getAlpha(),maxEndColorMultiplier.getAlpha()));
	
}



void DefaultParticleComponent::updateParticle(float completionRatio, int updateCount, float time){
	if (updateLife != 0) {
		if(updateLife >0)completionRatio = -(static_cast<float>(updateLife-initialUpdateLife)/ static_cast<float>(initialUpdateLife));
		Vector2 scale = startScale+((endScale - startScale) * completionRatio);
		transform->setScale(scale);
		
		colorTransform->setColorMultiplier(
			startColorMultiplier.getRed() +((endColorMultiplier.getRed() - startColorMultiplier.getRed()) *completionRatio),
			startColorMultiplier.getGreen() +((endColorMultiplier.getGreen() - startColorMultiplier.getGreen()) *completionRatio),
			startColorMultiplier.getBlue() +((endColorMultiplier.getBlue() - startColorMultiplier.getBlue()) *completionRatio),
			startColorMultiplier.getAlpha() +((endColorMultiplier.getAlpha() - startColorMultiplier.getAlpha()) *completionRatio)
		);
		if(updateLife >0)updateLife--;
	}
	else{
		phasesIterator++;

		if (phasesIterator >= phases->size()) {
			standby();
		}
		else{
			initParticle();
		}
	}
}


void DefaultParticleComponent::initializeConnections(){
	this->addConnection(new ComponentConnection<Transform>(&this->transform));
	this->addConnection(new ComponentConnection<Visibility>(&this->visibility));
	this->addConnection(new ComponentConnection<Speed>(&this->speed));
	this->addConnection(new ComponentConnection<ColorTransform>(&this->colorTransform));
	this->refreshConnections();
}

