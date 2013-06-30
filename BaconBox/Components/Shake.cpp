#include "BaconBox/Components/Shake.h"

#include <cmath>
#include <algorithm>

#include "BaconBox/Core/Entity.h"
#include "BaconBox/Helper/Random.h"
#include "BaconBox/Console.h"
#include "BaconBox/Components/ComponentConnection.h"
#include "BaconBox/Core/Engine.h"
#include "BaconBox/Display/Window/MainWindow.h"

namespace BaconBox {
	BB_ID_IMPL(Shake);

	int Shake::MESSAGE_START_SHAKE = IDManager::generateID();
	
	int Shake::MESSAGE_SHAKE_OFFSET_CHANGED = IDManager::generateID();

	Shake::Shake() : Component(), axis(BOTH), duration(0.0), offset(), shakeStopwatch() {
	}

	Shake::Shake(const Shake &src) : Component(src), axis(src.axis), duration(src.duration), offset(src.offset), shakeStopwatch(src.shakeStopwatch) {
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

		double timeSinceStarted = std::max(this->shakeStopwatch.getTime(), 0.0);
		
		if (timeSinceStarted < this->duration) {
			Vector2ChangedData data;
			data.oldValue = this->offset;
			
			// We calculate a random offset.
			float tmpIntensity = (timeSinceStarted == 0.0) ? (this->intensity) : ((1.0f - (timeSinceStarted / this->duration)) * this->intensity);
			
			if ((this->axis & HORIZONTAL) == HORIZONTAL) {
				this->offset.x = Random::getRandomFloat(-tmpIntensity, tmpIntensity) * Engine::getMainWindow().getContextWidth();
				
			} else {
				this->offset.x = 0.0f;
			}
			
			if ((this->axis & VERTICAL) == VERTICAL) {
				this->offset.y = Random::getRandomFloat(-tmpIntensity, tmpIntensity) * Engine::getMainWindow().getContextWidth();
				
			} else {
				this->offset.y = 0.0f;
			}
			
			data.newValue = this->offset;
			this->sendMessage(Entity::BROADCAST, MESSAGE_SHAKE_OFFSET_CHANGED, &data);
			
		} else if (this->offset.x != 0.0f || this->offset.y != 0.0f) {
			Vector2ChangedData data(this->offset, Vector2());
			this->offset.x = this->offset.y = 0.0f;
			this->sendMessage(Entity::BROADCAST, MESSAGE_SHAKE_OFFSET_CHANGED, &data);
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
	
	const Vector2 &Shake::getOffset() const {
		return this->offset;
	}

	ShakeProxy::ShakeProxy(Entity *entity, bool mustAddComponent) : BB_PROXY_CONSTRUCTOR(new Shake()) {
	}

	void ShakeProxy::shake(float newIntensity, double newDuration,
	                       bool forceReset, Shake::ShakeAxis newAxis) {
		reinterpret_cast<Shake *>(this->component)->shake(newIntensity, newDuration, forceReset, newAxis);
	}
	
	const Vector2 &ShakeProxy::getOffset() const {
		return reinterpret_cast<Shake *>(this->component)->getOffset();
	}
}
