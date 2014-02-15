#include "BaconBox/Components/ParticleEmitterComponent.h"
#include "BaconBox/Components/ParticleComponent.h"
#include "BaconBox/ParticleEmitter.h"
#include "BaconBox/Helper/Random.h"

#include "BaconBox/Components/ComponentConnection.h"
#include "BaconBox/Core/Entity.h"
using namespace BaconBox;

	BB_ID_IMPL(ParticleEmitterComponent);
	
ParticleEmitterComponent::ParticleEmitterComponent() : Component(), updateCount(0), completionRatio(0.0f), phases(), isOn(false), minEmited(1), maxEmited(1), emitCycle(NONE),particles() {
		this->initializeConnections();
	}


void ParticleEmitterComponent::setParticles(std::vector<MovieClipEntity*> & mcs, MovieClipEntity * parent){
	if(!parent)parent = this->getEntity<ParticleEmitter>();

	particles.clear();
	for (std::vector<MovieClipEntity*>::iterator i  = mcs.begin(); i != mcs.end(); i++) {
		ParticleComponent * particleComponent = (*i)->getComponent<ParticleComponent>();
			particles.push_back(particleComponent);
			particleComponent->standby();
			parent->addChild(*i);
		particleComponent->setPhases(phases);
	}
}


	ParticleEmitterComponent::~ParticleEmitterComponent() {
	}

	void ParticleEmitterComponent::initializeConnections() {
//		this->addConnection(new ComponentConnection<Transform>(&this->transform));
//		this->refreshConnections();
	}


void ParticleEmitterComponent::setNbEmited(int minEmited, int maxEmited){
	if(maxEmited < minEmited) maxEmited = minEmited;
	this->minEmited = minEmited;
	this->maxEmited = maxEmited;
}

void ParticleEmitterComponent::emit(){
	int emitCount = Random::getRandomInteger(minEmited, maxEmited);
	std::vector<ParticleComponent*>::iterator i = particles.begin();
	while (emitCount > 0 && i != particles.end()) {
		ParticleComponent * particle = (*i);
		i++;
		if (particle->status == ParticleComponent::STANDBY) {
			particle->initParticle();
			emitCount--;
		}
	}
}
void ParticleEmitterComponent::addPhase(ParicleInitInfo * initializationData){
	this->phases.push_back(initializationData);
}

void ParticleEmitterComponent::setUpdateCycle(int minUpdate, int maxUpdate){
	emitCycle = UPDATE;
	if(maxUpdate < minUpdate) maxUpdate = minUpdate;
	cycleParams.updateParams.minUpdate = minUpdate;
	cycleParams.updateParams.maxUpdate = maxUpdate;
	cycleParams.updateParams.nextUpdate = Random::getRandomInteger(minUpdate, maxUpdate);
	cycleParams.updateParams.updateIncr = 1;
}
//
void ParticleEmitterComponent::update(){
	if(isOn){
		updateCount++;
		if(emitCycle == UPDATE){
			if(cycleParams.updateParams.updateIncr % cycleParams.updateParams.nextUpdate == 0){
				emit();
				cycleParams.updateParams.nextUpdate = Random::getRandomInteger(cycleParams.updateParams.minUpdate, cycleParams.updateParams.maxUpdate);
				cycleParams.updateParams.updateIncr = 1;
			}
			else{
				cycleParams.updateParams.updateIncr++;
			}
		}
	}
	for (std::vector<ParticleComponent*>::iterator i = particles.begin(); i != particles.end(); i++) {
		ParticleComponent * particle = (*i);
		if (particle->status == ParticleComponent::USED) {
			particle->updateParticle(completionRatio, updateCount, 0);
		}
	}
}


void ParticleEmitterComponent::start(){
	isOn = true;
}

void ParticleEmitterComponent::stop(){
	isOn = false;
	updateCount = 0;
}

	ParticleEmitterComponentProxy::ParticleEmitterComponentProxy(Entity *entity, bool mustAddComponent) : BB_PROXY_CONSTRUCTOR(new ParticleEmitterComponent()) {
	}

void ParticleEmitterComponentProxy::start(){
	reinterpret_cast<ParticleEmitterComponent *>(component)->start();
}
void ParticleEmitterComponentProxy::stop(){
	reinterpret_cast<ParticleEmitterComponent *>(component)->stop();
}

void ParticleEmitterComponentProxy::setUpdateCycle(int minUpdate, int maxUpdate){
	reinterpret_cast<ParticleEmitterComponent *>(component)->setUpdateCycle(minUpdate, maxUpdate);
}

void ParticleEmitterComponentProxy::setNbEmited(int minEmited, int maxEmited){
	reinterpret_cast<ParticleEmitterComponent *>(component)->setNbEmited(minEmited, maxEmited);
}
void ParticleEmitterComponentProxy::update(){
	reinterpret_cast<ParticleEmitterComponent *>(component)->update();
}

void ParticleEmitterComponentProxy::emit(){
	reinterpret_cast<ParticleEmitterComponent *>(component)->emit();
}

void ParticleEmitterComponentProxy::addPhase(ParicleInitInfo * initializationData){
	reinterpret_cast<ParticleEmitterComponent *>(component)->addPhase(initializationData);
}

void ParticleEmitterComponentProxy::setParticles(std::vector<MovieClipEntity*> & mcs, MovieClipEntity * parent){
	reinterpret_cast<ParticleEmitterComponent *>(component)->setParticles(mcs, parent);
}
