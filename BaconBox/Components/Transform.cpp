#include "Transform.h"

#include "BaconBox/Core/Entity.h"
#include "BaconBox/Helper/Vector2ChangedData.h"
#include "BaconBox/Console.h"

namespace BaconBox {
	 BB_ID_IMPL(Transform);
	int Transform::MESSAGE_GET_POSITION = IDManager::generatetID();
	int Transform::MESSAGE_GET_ROTATION = IDManager::generatetID();
	int Transform::MESSAGE_GET_SCALE = IDManager::generatetID();
	int Transform::MESSAGE_SET_POSITION = IDManager::generatetID();
	int Transform::MESSAGE_SET_ROTATION = IDManager::generatetID();
	int Transform::MESSAGE_SET_SCALE = IDManager::generatetID();
	int Transform::MESSAGE_POSITION_CHANGED = IDManager::generatetID();
	int Transform::MESSAGE_ROTATION_CHANGED = IDManager::generatetID();
	int Transform::MESSAGE_SCALE_CHANGED = IDManager::generatetID();
	
	Transform::Transform() : Component(), position(), rotation(0.0f), scale(1.0f, 1.0f) {
	}

	Transform::Transform(const Transform &src) : Component(src), position(src.position), rotation(src.rotation), scale(src.scale) {
	}

	Transform::~Transform() {
	}

	Transform &Transform::operator=(const Transform &src) {
		if (this != &src) {
			setPosition(src.getPosition());
			setRotation(src.getRotation());
			setScale(src.getScale());
		}

		return *this;
	}

	Transform *Transform::clone() const {
		return new Transform(*this);
	}
	
	void Transform::receiveMessage(int senderID, int destID, int message, void *data) {
		if (destID != Transform::ID) {
			return;
		}
		
		if (message == Transform::MESSAGE_GET_POSITION) {
			*reinterpret_cast<Vector2 *>(data) = this->getPosition();
		} else if (message == Transform::MESSAGE_GET_ROTATION) {
			*reinterpret_cast<float *>(data) = this->getRotation();
		} else if (message == Transform::MESSAGE_GET_SCALE) {
			*reinterpret_cast<Vector2 *>(data) = this->getScale();
		} else if (message == Transform::MESSAGE_SET_POSITION) {
			this->setPosition(*reinterpret_cast<Vector2 *>(data));
		} else if (message == Transform::MESSAGE_SET_ROTATION) {
			this->setRotation(*reinterpret_cast<float *>(data));
		} else if (message == Transform::MESSAGE_SET_SCALE) {
			this->setScale(*reinterpret_cast<Vector2 *>(data));
		}
	}


	const Vector2 &Transform::getPosition() const {
		return this->position;
	}

	void Transform::setPosition(const Vector2 &newPosition) {
		Vector2ChangedData data(this->position, newPosition);
		this->position = newPosition;
		sendMessage(Entity::BROADCAST, MESSAGE_POSITION_CHANGED, &(data));
	}

	float Transform::getRotation() const {
		#if !defined(BB_FLASH_PLATEFORM)
			return this->rotation * -1;
		#endif
		return this->rotation;
	}

	void Transform::setRotation(float newRotation) {
		   #if !defined(BB_FLASH_PLATEFORM)
			newRotation *= -1;
		#endif
		ValueChangedData<float> data(this->rotation, newRotation);
		this->rotation = newRotation;

		sendMessage(Entity::BROADCAST, MESSAGE_ROTATION_CHANGED, &(data));
	}

	const Vector2 &Transform::getScale() const {
		return this->scale;
	}

	void Transform::setScale(const Vector2 &newScale) {
		Vector2ChangedData data(this->scale, newScale);
		this->scale = newScale;
		sendMessage(Entity::BROADCAST, MESSAGE_SCALE_CHANGED, &(data));
	}
	
	
	TransformProxy::TransformProxy(Entity* entity, bool mustAddComponent): BB_PROXY_CONSTRUCTOR(new Transform())  {
	}
	    
	    
	const Vector2 &TransformProxy::getPosition() const{
	    return reinterpret_cast<Transform*>(component)->getPosition();
	}

	void TransformProxy::setPosition(const Vector2 &newPosition){
	    reinterpret_cast<Transform*>(component)->setPosition(newPosition);
	}

	float TransformProxy::getRotation() const{
	    return reinterpret_cast<Transform*>(component)->getRotation();
	}

	void TransformProxy::setRotation(float newRotation){
	    reinterpret_cast<Transform*>(component)->setRotation(newRotation);
	}

	const Vector2 &TransformProxy::getScale() const{
	    return reinterpret_cast<Transform*>(component)->getScale();
	}

	void TransformProxy::setScale(const Vector2 &newScale){
	    reinterpret_cast<Transform*>(component)->setScale(newScale);
	}
	
}