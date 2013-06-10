#include "Transform.h"

#include "BaconBox/Core/Entity.h"
#include "BaconBox/Console.h"
#include "BaconBox/Helper/MathHelper.h"
#include "BaconBox/Components/MatrixComponent.h"
#include "BaconBox/Components/DefaultMatrix.h"

namespace BaconBox {
	 BB_ID_IMPL(Transform);
	int Transform::MESSAGE_GET_POSITION = IDManager::generateID();
	int Transform::MESSAGE_GET_ROTATION = IDManager::generateID();
	int Transform::MESSAGE_GET_SCALE = IDManager::generateID();
	int Transform::MESSAGE_SET_POSITION = IDManager::generateID();
	int Transform::MESSAGE_SET_ROTATION = IDManager::generateID();
	int Transform::MESSAGE_SET_SCALE = IDManager::generateID();
	int Transform::MESSAGE_POSITION_CHANGED = IDManager::generateID();
	int Transform::MESSAGE_ROTATION_CHANGED = IDManager::generateID();
	int Transform::MESSAGE_SCALE_CHANGED = IDManager::generateID();

	Transform::Transform() : Component(), position(), rotation(0.0f), scale(1.0f, 1.0f), matrixComponent(NULL){
		initializeConnections();
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

	void Transform::initializeConnections(){
		this->addConnection(new ComponentConnection<MatrixComponent>(&this->matrixComponent));
		this->refreshConnections();
	}

	
	
	void Transform::receiveMessage(int senderID, int destID, int message, void *data) {
	    Component::receiveMessage(senderID, destID, message, data);
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


	const Vector2 &Transform::getRealPosition() {
		if(matrixComponent){
			realPosition = matrixComponent->getConcatMatrix().multiplyWithVector(Vector2());
			return realPosition;
		}
		else{
			return getPosition();
		}
	}

	void Transform::setPosition(const Vector2 &newPosition, bool withMessage) {
		Vector2ChangedData data(this->position, newPosition);
		this->position = newPosition;
		if(withMessage){
			sendMessage(Entity::BROADCAST, MESSAGE_POSITION_CHANGED, &(data));
		}
	}

	float Transform::getRotation() const {
		return this->rotation;
	}

	void Transform::setRotation(float newRotation, bool withMessage) {
		ValueChangedData<float> data(this->rotation, newRotation);
		this->rotation = newRotation;
		if(withMessage){
			sendMessage(Entity::BROADCAST, MESSAGE_ROTATION_CHANGED, &(data));
		}
	}

	const Vector2 &Transform::getScale() const {
		return this->scale;
	}

	void Transform::setScale(const Vector2 &newScale, bool withMessage) {
		Vector2ChangedData data(this->scale, newScale);
		this->scale = newScale;
		if(withMessage){
			sendMessage(Entity::BROADCAST, MESSAGE_SCALE_CHANGED, &(data));
		}
	}







	TransformProxy::TransformProxy(Entity* entity, bool mustAddComponent): BB_PROXY_CONSTRUCTOR(new Transform())  {
	}



	const Vector2 &TransformProxy::getPosition() const{
	    return reinterpret_cast<Transform*>(component)->getPosition();
	}

    const Vector2 &TransformProxy::getRealPosition() const{
	    return reinterpret_cast<Transform*>(component)->getRealPosition();
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

    void TransformProxy::setTransform(Transform * transform){
        component = transform;
	    entity->addComponent(transform);
    }


}
