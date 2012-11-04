#include "Transform.h"

namespace BaconBox {
	Transform::Transform() : Component(), position(), rotation(0.0f), scale() {
	}

	Transform::Transform(const Transform &src) : Component(), position(src.position), rotation(src.rotation), scale(src.scale) {
	}

	Transform::~Transform() {
	}

	Transform &Transform::operator=(const Transform &src) {
		if (this != &src) {
			this->position = src.position;
			this->rotation = src.rotation;
			this->scale = src.scale;
		}

		return *this;
	}

	Transform *Transform::clone() const {
		return new Transform(*this);
	}

	void Transform::receiveMessage(int id, int message, void *data) {
		if (id == ID<Transform>::NUMBER) {
			switch (message) {
			case Transform::MESSAGE_GET_POSITION:
				*reinterpret_cast<Vector2 *>(data) = this->getPosition();
				break;

			case Transform::MESSAGE_GET_ROTATION:
				*reinterpret_cast<float *>(data) = this->getRotation();
				break;

			case Transform::MESSAGE_GET_SCALE:
				*reinterpret_cast<Vector2 *>(data) = this->getScale();
				break;

			case Transform::MESSAGE_SET_POSITION:
				this->setPosition(*reinterpret_cast<Vector2 *>(data));
				break;

			case Transform::MESSAGE_SET_ROTATION:
				this->setRotation(*reinterpret_cast<float *>(data));
				break;

			case Transform::MESSAGE_SET_SCALE:
				this->setScale(*reinterpret_cast<Vector2 *>(data));
				break;

			default:
				break;
			}
		}
	}

	const Vector2 &Transform::getPosition() const {
		return this->position;
	}

	void Transform::setPosition(const Vector2 &newPosition) {
		this->position = newPosition;
	}

	float Transform::getRotation() const {
		return this->rotation;
	}

	void Transform::setRotation(float newRotation) {
		this->rotation = newRotation;
	}

	const Vector2 &Transform::getScale() const {
		return this->scale;
	}

	void Transform::setScale(const Vector2 &newScale) {
		this->scale = newScale;
	}
}