#include "Speed.h"

#include "BaconBox/Components/Transform.h"
#include "BaconBox/Components/ComponentConnection.h"

namespace BaconBox {
	Speed::Speed() : Component(), velocity(), acceleration(), angularVelocity(0.0f), updateStopwatch() {
		this->initializeConnections();
	}

	Speed::Speed(const Speed &src) : Component(src), velocity(src.velocity), acceleration(src.acceleration), angularVelocity(src.angularVelocity), updateStopwatch(src.updateStopwatch) {
		this->initializeConnections();
	}

	Speed::~Speed() {
	}

	Speed &Speed::operator=(const Speed &src) {
		if (this != &src) {
			this->velocity = src.velocity;
			this->acceleration = src.acceleration;
			this->angularVelocity = src.angularVelocity;
			this->updateStopwatch = src.updateStopwatch;
		}

		return *this;
	}

	Speed *Speed::clone() const {
		return new Speed(*this);
	}

	void Speed::receiveMessage(int senderID, int destID, int message, void *data) {
	}

	void Speed::update() {
		if (this->transform) {
			float timeElapsed = static_cast<float>(this->updateStopwatch.getTime());

			this->velocity += this->acceleration * timeElapsed;

			if (this->velocity.x != 0.0f || this->velocity.y != 0.0f) {
				this->transform->setPosition(this->transform->getPosition() + (this->velocity * timeElapsed));
			}

			if (this->angularVelocity != 0.0f) {
				this->transform->setRotation(this->transform->getRotation() + this->angularVelocity * timeElapsed);
			}
		}

		this->updateStopwatch.stop();
		this->updateStopwatch.start();
	}

	const Vector2 &Speed::getVelocity() const {
		return this->velocity;
	}

	void Speed::setVelocity(const Vector2 &newVelocity) {
		this->velocity = newVelocity;
	}

	void Speed::setXVelocity(float newXVelocity) {
		this->velocity.x = newXVelocity;
	}

	void Speed::setYVelocity(float newYVelocity) {
		this->velocity.y = newYVelocity;
	}

	const Vector2 &Speed::getAcceleration() const {
		return this->acceleration;
	}

	void Speed::setAcceleration(const Vector2 &newAcceleration) {
		this->acceleration = newAcceleration;
	}

	void Speed::setXAcceleration(float newXAcceleration) {
		this->acceleration.x = newXAcceleration;
	}

	void Speed::setYAcceleration(float newYAcceleration) {
		this->acceleration.y = newYAcceleration;
	}

	float Speed::getAngularVelocity() const {
		return this->angularVelocity;
	}

	void Speed::setAngularVelocity(float newAngularVelocity) {
		this->angularVelocity = newAngularVelocity;
	}

	void Speed::initializeConnections() {
		this->addConnection(new ComponentConnection<Transform>(&this->transform));
		this->refreshConnections();
	}

	SpeedProxy::SpeedProxy(Entity *entity, bool mustAddComponent) : BB_PROXY_CONSTRUCTOR(new Speed()) {
	}

	const Vector2 &SpeedProxy::getVelocity() const {
		return reinterpret_cast<Speed *>(this->component)->getVelocity();
	}

	void SpeedProxy::setVelocity(const Vector2 &newVelocity) {
		reinterpret_cast<Speed *>(this->component)->setVelocity(newVelocity);
	}

	void SpeedProxy::setXVelocity(float newXVelocity) {
		reinterpret_cast<Speed *>(this->component)->setXVelocity(newXVelocity);
	}

	void SpeedProxy::setYVelocity(float newYVelocity) {
		reinterpret_cast<Speed *>(this->component)->setYVelocity(newYVelocity);
	}

	const Vector2 &SpeedProxy::getAcceleration() const {
		return reinterpret_cast<Speed *>(this->component)->getAcceleration();
	}

	void SpeedProxy::setAcceleration(const Vector2 &newAcceleration) {
		reinterpret_cast<Speed *>(this->component)->setAcceleration(newAcceleration);
	}

	void SpeedProxy::setXAcceleration(float newXAcceleration) {
		reinterpret_cast<Speed *>(this->component)->setXAcceleration(newXAcceleration);
	}

	void SpeedProxy::setYAcceleration(float newYAcceleration) {
		reinterpret_cast<Speed *>(this->component)->setYAcceleration(newYAcceleration);
	}

	float SpeedProxy::getAngularVelocity() const {
		return reinterpret_cast<Speed *>(this->component)->getAngularVelocity();
	}

	void SpeedProxy::setAngularVelocity(float newAngularVelocity) {
		reinterpret_cast<Speed *>(this->component)->setAngularVelocity(newAngularVelocity);
	}
}
