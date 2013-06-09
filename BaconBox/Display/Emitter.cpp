#include "BaconBox/Display/Emitter.h"

#include "BaconBox/Helper/Random.h"

namespace BaconBox {
	Emitter::Emitter() : minLifetime(0.2), maxLifetime(0.8), minForce(20.0), maxForce(40.0), minAngle(-180.0), maxAngle(180.0), minAngularVelocity(0.0), maxAngularVelocity(0.0), rotationDirection(Emitter::NONE) {
	}

	Emitter::Emitter(const Emitter &src) : minLifetime(src.minLifetime), maxLifetime(src.maxLifetime), minForce(src.minForce), maxForce(src.maxForce), minAngle(src.minAngle), maxAngle(src.maxAngle), minAngularVelocity(src.minAngularVelocity), maxAngularVelocity(src.maxAngularVelocity), rotationDirection(src.rotationDirection) {
	}

	Emitter::~Emitter() {
	}

	Emitter &Emitter::operator=(const Emitter &src) {
		if (this != &src) {
			this->minLifetime = src.minLifetime;
			this->maxLifetime = src.maxLifetime;
			this->minForce = src.minForce;
			this->maxForce = src.maxForce;
			this->minAngle = src.minAngle;
			this->maxAngle = src.maxAngle;
			this->minAngularVelocity = src.minAngularVelocity;
			this->maxAngularVelocity = src.maxAngularVelocity;
			this->rotationDirection = src.rotationDirection;
		}

		return *this;
	}

	double Emitter::getMinLifetime() const {
		return this->minLifetime;
	}
	void Emitter::setMinLifetime(double newMinLifetime) {
		this->minLifetime = newMinLifetime;
	}

	double Emitter::getMaxLifetime() const {
		return this->maxLifetime;
	}
	void Emitter::setMaxLifetime(double newMaxLifetime) {
		this->maxLifetime = newMaxLifetime;
	}

	float Emitter::getMinForce() const {
		return this->minForce;
	}
	void Emitter::setMinForce(float newMinForce) {
		this->minForce = newMinForce;
	}

	float Emitter::getMaxForce() const {
		return this->maxForce;
	}
	void Emitter::setMaxForce(float newMaxForce) {
		this->maxForce = newMaxForce;
	}

	float Emitter::getMinAngle() const {
		return this->minAngle;
	}
	void Emitter::setMinAngle(float newMinAngle) {
		this->minAngle = newMinAngle;
	}

	float Emitter::getMaxAngle() const {
		return this->maxAngle;
	}
	void Emitter::setMaxAngle(float newMaxAngle) {
		this->maxAngle = newMaxAngle;
	}

	float Emitter::getMinAngularVelocity() const {
		return this->minAngularVelocity;
	}
	void Emitter::setMinAngularVelocity(float newMinAngularVelocity) {
		this->minAngularVelocity = newMinAngularVelocity;
	}

	float Emitter::getMaxAngularVelocity() const {
		return this->maxAngularVelocity;
	}
	void Emitter::setMaxAngularVelocity(float newMaxAngularVelocity) {
		this->maxAngularVelocity = newMaxAngularVelocity;
	}

	int Emitter::getRotationDirection() const {
		return this->rotationDirection;
	}
	void Emitter::setRotationDirection(int newRotationDirection) {
		this->rotationDirection = newRotationDirection;
	}
	
	void Emitter::emitParticle() {
		double lifetime = Random::getRandomDouble(this->minLifetime, this->maxLifetime);
		float force = Random::getRandomFloat(this->minForce, this->maxForce);
		float angle = Random::getRandomFloat(this->minAngle, this->maxAngle);
		float angularVelocity = Random::getRandomFloat(this->minAngularVelocity, this->maxAngularVelocity);
		
		this->emitParticle(lifetime, force, angle, angularVelocity, this->rotationDirection);
	}
}
