#include "Transform.h"

#include "BaconBox/Core/Entity.h"
#include "BaconBox/Helper/Vector2ChangedData.h"
#include "BaconBox/Console.h"

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
	int Transform::MESSAGE_MATRIX_CHANGED = IDManager::generateID();
	
	
	Transform::Transform() : Component(), position(), rotation(0.0f), scale(1.0f, 1.0f), matrix() {
	}

	Transform::Transform(const Transform &src) : Component(src), position(src.position), rotation(src.rotation), scale(src.scale), matrix(src.matrix) {
	}

	Transform::~Transform() {
	}

	Transform &Transform::operator=(const Transform &src) {
		if (this != &src) {

			setPosition(src.getPosition());
			setRotation(src.getRotation());
			setScale(src.getScale());
			this->matrix = src.matrix;
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
		Vector2 diff = data.newValue - data.oldValue;
		this->matrix.translate(diff.x, diff.y);
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
		this->matrix.rotate(data.newValue - data.oldValue);
		sendMessage(Entity::BROADCAST, MESSAGE_ROTATION_CHANGED, &(data));
	}

	const Vector2 &Transform::getScale() const {
		return this->scale;
	}

	void Transform::setScale(const Vector2 &newScale) {
		Vector2ChangedData data(this->scale, newScale);
		this->scale = newScale;
		Vector2 diff = Vector2(data.newValue.x / data.oldValue.x, data.newValue.y / data.oldValue.y);
		this->matrix.scale(diff.x, diff.y);
		sendMessage(Entity::BROADCAST, MESSAGE_SCALE_CHANGED, &(data));
	}
	
	Matrix2 & Transform::getMatrix(){
	    return matrix;
	}
	
	void Transform::setMatrix(const Matrix2 & m){
	    Vector2 origin = Vector2() * m;
	    Vector2 endingX = Vector2(1,0) * m;
	    Vector2 endingY = Vector2(0,1) * m;
	    
	    this->matrix = m;
	    this->position = origin;
	    this->rotation = (endingX - origin).getAngle();
	    this->scale.x = (endingX - origin).getLength();
	    this->scale.y = (endingY - origin).getLength();
	    sendMessage(Entity::BROADCAST, MESSAGE_MATRIX_CHANGED, &(data));

	}
	
	TransformProxy::TransformProxy(Entity* entity, bool mustAddComponent): BB_PROXY_CONSTRUCTOR(new Transform())  {
	}
	    
	void TransformProxy::setMatrix(const Matrix2 & m){
		reinterpret_cast<Transform*>(component)->setMatrix(m);
	}
			
	Matrix2 & TransformProxy::getMatrix(){
	    return reinterpret_cast<Transform*>(component)->getMatrix();
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