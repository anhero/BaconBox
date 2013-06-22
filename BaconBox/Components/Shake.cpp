#include "Shake.h"

#include "BaconBox/Components/Transform.h"
#include "BaconBox/Components/ComponentConnection.h"
#include "BaconBox/Helper/Random.h"
#include "BaconBox/Console.h"

namespace BaconBox {
	Shake::Shake() : Component(), transform(NULL) {
		this->initializeConnections();
	}
	
	Shake::Shake(const Shake &src) : Component(src), transform(NULL) {
		this->initializeConnections();
	}
	
	Shake::~Shake() {
	}
	
	Shake &Shake::operator=(const Shake &src) {
		if (this != &src) {
		}
		
		return *this;
	}
	
	Shake *Shake::clone() const {
		return new Shake(*this);
	}
	
	void Shake::update() {
		this->Component::update();
		
		if (this->shakeStopwatch.getTime() < this->duration) {
			double timeSinceStarted = this->shakeStopwatch.getTime();
			// SHAKE
			float tmpIntensity = (timeSinceStarted == 0.0) ?(this->intensity) : ((1.0f - (timeSinceStarted / this->duration)) * this->intensity);
		} else {
			if (this->transform) {
				this->transform->setPosition(this->initialPosition);
			}
			
			this->shakeStopwatch.stop();
		}
	}
	
	void Shake::shake(double newDuration, float newIntensity) {
		this->duration = newDuration;
		this->intensity = newIntensity;
		
		if (!shakeStopwatch.isStarted()) {
			if (this->transform) {
				this->initialPosition = this->transform->getPosition();
			} else {
				this->initialPosition = Vector2();
			}
		}
		
		this->shakeStopwatch.stop();
		this->shakeStopwatch.start();
	}
	
	void Shake::initializeConnections() {
		this->addConnection(new ComponentConnection<Transform>(&this->transform));
		this->refreshConnections();
	}
}
