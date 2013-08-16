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

	Transform::Transform() : Component(), _position(), _rotation(0.0f), _scale(1.0f, 1.0f), matrixComponent(NULL),
	x(this, &Transform::getX, &Transform::setX),
	y(this, &Transform::getY, &Transform::setY),
	scaleX(this, &Transform::getScaleX, &Transform::setScaleX),
	scaleY(this, &Transform::getScaleX, &Transform::setScaleX),
	rotation(this, &Transform::getRotation, &Transform::setRotationInternal){
		initializeConnections();
	}

	Transform::Transform(const Transform &src) : Component(src), _position(src._position), _rotation(src._rotation), _scale(src._scale),
	x(this, &Transform::getX, &Transform::setX),
	y(this, &Transform::getY, &Transform::setY),
	scaleX(this, &Transform::getScaleX, &Transform::setScaleX),
	scaleY(this, &Transform::getScaleX, &Transform::setScaleX),
	rotation(this, &Transform::getRotation, &Transform::setRotationInternal){
		
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
	
	void Transform::setX(float x){
		_position.x = x;
		setPosition(_position);
	}
	
	void Transform::setY(float y){
		_position.y = y;
		setPosition(_position);
	}
	void Transform::setScaleX(float x){
		_scale.x = x;
		setScale(_scale);

	}
	void Transform::setScaleY(float y){
		_scale.y = y;
		setScale(_scale);
	}
	
	void Transform::setRotationInternal(float rotation){
		setRotation(rotation);
	}

	
	float Transform::getX() const{
		return getPosition().x;
	}
	float Transform::getY() const{
		return getPosition().y;
	}
		
	float Transform::getScaleX() const{
		return getScale().x;
	}
	float Transform::getScaleY() const{
		return getScale().y;
	}
	


	Transform *Transform::clone() const {
		return new Transform(*this);
	}

	void Transform::initializeConnections() {
		this->addConnection(new ComponentConnection<MatrixComponent>(&this->matrixComponent));
		this->refreshConnections();
	}

	void Transform::receiveMessage(int senderID, int destID, int message, void *data) {
		this->Component::receiveMessage(senderID, destID, message, data);

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
		return this->_position;
	}


	const Vector2 &Transform::getRealPosition() {
		if (matrixComponent) {
			realPosition = matrixComponent->getConcatMatrix().multiplyWithVector(Vector2());
			return realPosition;

		} else {
			return getPosition();
		}
	}

	void Transform::setPosition(const Vector2 &newPosition, bool withMessage) {
		Vector2ChangedData data(this->_position, newPosition);
		this->_position = newPosition;

		if (withMessage) {
			sendMessage(Entity::BROADCAST, MESSAGE_POSITION_CHANGED, &(data));
		}
	}

	float Transform::getRotation() const {
		return this->_rotation;
	}

	void Transform::setRotation(float newRotation, bool withMessage) {
		ValueChangedData<float> data(this->_rotation, newRotation);
		this->_rotation = newRotation;

		if (withMessage) {
			sendMessage(Entity::BROADCAST, MESSAGE_ROTATION_CHANGED, &(data));
		}
	}

	const Vector2 &Transform::getScale() const {
		return this->_scale;
	}

	void Transform::setScale(const Vector2 &newScale, bool withMessage) {
		Vector2ChangedData data(this->_scale, newScale);
		this->_scale = newScale;

		if (withMessage) {
			sendMessage(Entity::BROADCAST, MESSAGE_SCALE_CHANGED, &(data));
		}
	}
	
	void TransformProxy::setProperties(Transform *transform){
		if(transform){
			x.setInstance(transform);
			y.setInstance(transform);
			scaleX.setInstance(transform);
			scaleY.setInstance(transform);
			rotation.setInstance(transform);
		}
	}


	TransformProxy::TransformProxy(Entity *entity, bool mustAddComponent): BB_PROXY_CONSTRUCTOR(new Transform()),
	x(NULL, &Transform::getX, &Transform::setX),
	y(NULL, &Transform::getY, &Transform::setY),
	scaleX(NULL, &Transform::getScaleX, &Transform::setScaleX),
	scaleY(NULL, &Transform::getScaleX, &Transform::setScaleX),
	rotation(NULL, &Transform::getRotation, &Transform::setRotationInternal)  {
		setProperties(static_cast<Transform*>(this->component));
	}

	const Vector2 &TransformProxy::getPosition() const {
		return reinterpret_cast<Transform *>(component)->getPosition();
	}

	const Vector2 &TransformProxy::getRealPosition() const {
		return reinterpret_cast<Transform *>(component)->getRealPosition();
	}

	void TransformProxy::setPosition(const Vector2 &newPosition) {
		reinterpret_cast<Transform *>(component)->setPosition(newPosition);
	}

	float TransformProxy::getRotation() const {
		return reinterpret_cast<Transform *>(component)->getRotation();
	}

	void TransformProxy::setRotation(float newRotation) {
		reinterpret_cast<Transform *>(component)->setRotation(newRotation);
	}

	const Vector2 &TransformProxy::getScale() const {
		return reinterpret_cast<Transform *>(component)->getScale();
	}

	void TransformProxy::setScale(const Vector2 &newScale) {
		reinterpret_cast<Transform *>(component)->setScale(newScale);
	}

	void TransformProxy::setTransform(Transform *transform) {
		component = transform;
		entity->addComponent(transform);
		setProperties(transform);
	}
}
