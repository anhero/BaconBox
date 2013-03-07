#include "Transform.h"

#include "BaconBox/Core/Entity.h"
#include "BaconBox/Console.h"
#include "BaconBox/Helper/MathHelper.h"

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
		updateMatrix(data, Vector2ChangedData(scale,scale), ValueChangedData<float>(rotation, rotation));
		sendMessage(Entity::BROADCAST, MESSAGE_POSITION_CHANGED, &(data));
	}

	float Transform::getRotation() const {
		return this->rotation;
	}

	void Transform::setRotation(float newRotation) {
		ValueChangedData<float> data(this->rotation, newRotation);
		this->rotation = newRotation;
		updateMatrix(Vector2ChangedData(position,position), Vector2ChangedData(scale, scale), data);
		sendMessage(Entity::BROADCAST, MESSAGE_ROTATION_CHANGED, &(data));
	}

	const Vector2 &Transform::getScale() const {
		return this->scale;
	}

	void Transform::setScale(const Vector2 &newScale) {
		Vector2ChangedData data(this->scale, newScale);
		this->scale = newScale;
		updateMatrix(Vector2ChangedData(position,position), data, ValueChangedData<float>(rotation, rotation));
		sendMessage(Entity::BROADCAST, MESSAGE_SCALE_CHANGED, &(data));
	}
	
	Matrix & Transform::getMatrix(){
	    return matrix;
	}
	
	
	void Transform::updateMatrix(Vector2ChangedData position, Vector2ChangedData scale, ValueChangedData<float> angle){
	    if(matrix.isSkewed()){
		throw; // TODO IMPLEMENT ME! This branch of the condition is broken.
		matrix.rotate(-angle.oldValue);
		matrix.translate(-position.oldValue);
		matrix.scale(Vector2(1/scale.oldValue.x, 1/scale.oldValue.y));
		
		Matrix temp;
		temp.scale(scale.newValue);
		temp.translate(position.newValue);
		temp.rotate(angle.newValue);
		matrix = matrix * temp;
		
	    }
	    else{
		float cos  = MathHelper::cos(-angle.newValue*MathHelper::AngleConvert<float>::DEGREES_TO_RADIANS);
		matrix.a = scale.newValue.x * cos;
		matrix.c = MathHelper::sin(-angle.newValue*MathHelper::AngleConvert<float>::DEGREES_TO_RADIANS);
		matrix.b = -matrix.c;
		matrix.d = scale.newValue.y * cos;
		matrix.tx = position.newValue.x;
		matrix.ty = position.newValue.y;
	    }
	}

	
	void Transform::setMatrix(const Matrix & m){
	    this->matrix = m;
	    if(!m.isSkewed()){
		rotation = MathHelper::asin(m.b);
		float cos = MathHelper::cos(rotation);
		scale.x = m.a/cos;
		scale.y = m.d/cos;
		position.x = m.tx;
		position.y = m.ty;
		rotation *= MathHelper::AngleConvert<float>::RADIANS_TO_DEGREES; 
	    }
//	    Vector2 origin = m.multiplyWithVector(Vector2());
//	    Vector2 endingX = m.multiplyWithVector(Vector2(1,0));
//	    Vector2 endingY = m.multiplyWithVector(Vector2(0,1));
//	    
//	    setPosition(origin);
//	    setScale(Vector2((endingX - origin).getLength(), (endingY - origin).getLength()));
//	    setRotation((endingX - origin).getAngle()+90);

	    sendMessage(Entity::BROADCAST, MESSAGE_MATRIX_CHANGED, &(this->matrix));

	}
	
	TransformProxy::TransformProxy(Entity* entity, bool mustAddComponent): BB_PROXY_CONSTRUCTOR(new Transform())  {
	}
	    
	void TransformProxy::setMatrix(const Matrix & m){
		reinterpret_cast<Transform*>(component)->setMatrix(m);
	}
			
	Matrix & TransformProxy::getMatrix(){
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