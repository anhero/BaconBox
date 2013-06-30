#include "BaconBox/Components/Shake.h"

#include <cmath>
#include <algorithm>

#include "BaconBox/Core/Entity.h"
#include "BaconBox/Helper/Random.h"
#include "BaconBox/Console.h"
#include "BaconBox/Components/SizeComponent.h"
#include "BaconBox/Components/ComponentConnection.h"

namespace BaconBox {
	BB_ID_IMPL(Component);
	
	int Shake::MESSAGE_START_SHAKE = IDManager::generateID();
	
	Shake::Shake() : Component(), axis(BOTH), duration(0.0), offset(), shakeStopwatch() {
		this->initializeConnections();
	}
	
	Shake::Shake(const Shake &src) : Component(src), axis(src.axis), duration(src.duration), offset(src.offset), shakeStopwatch(src.shakeStopwatch) {
		this->initializeConnections();
	}
	
	Shake::~Shake() {
	}
	
	Shake &Shake::operator=(const Shake &src) {
		if (this != &src) {
			this->axis = src.axis;
			this->duration = src.duration;
			this->offset = src.offset;
			this->shakeStopwatch = src.shakeStopwatch;
		}
		
		return *this;
	}
	
	Shake *Shake::clone() const {
		return new Shake(*this);
	}
	
	void Shake::receiveMessage(int senderID, int destID, int message, void *data) {
		this->Component::receiveMessage(senderID, destID, message, data);
	}
	
	void Shake::update() {
		this->Component::update();
		
		// We make sure we have a valid size component.
		if (this->size) {
			double timeSinceStarted = std::max(this->shakeStopwatch.getTime(), 0.0);
			
			if (timeSinceStarted < this->duration) {
				// We calculate a random offset.
				float tmpIntensity = (timeSinceStarted == 0.0) ? (this->intensity) : ((1.0f - (timeSinceStarted / this->duration)) * this->intensity);
				
				if ((this->axis & HORIZONTAL) == HORIZONTAL) {
					this->offset.x = Random::getRandomFloat(-tmpIntensity, tmpIntensity) * this->size->getWidth();
				} else {
					this->offset.x = 0.0f;
				}
				
				if ((this->axis & VERTICAL) == VERTICAL) {
					this->offset.y = Random::getRandomFloat(-tmpIntensity, tmpIntensity) * this->size->getHeight();
				} else {
					this->offset.y = 0.0f;
				}
			} else {
				this->offset.x = this->offset.y = 0.0f;
			}
		}
	}
	
	void Shake::shake(float newIntensity, double newDuration, bool forceReset,
					  ShakeAxis newAxis) {
		if (forceReset || newIntensity > this->intensity) {
			this->intensity = std::abs(newIntensity);
			this->duration = std::max(newDuration, 0.0);
			this->axis = newAxis;
			this->shakeStopwatch.stop();
			this->shakeStopwatch.start();
			this->sendMessage(Entity::BROADCAST, MESSAGE_START_SHAKE, this);
		}
	}
	
	void Shake::initializeConnections(){
		this->addConnection(new ComponentConnection<SizeComponent>(&this->size));
	}
}
