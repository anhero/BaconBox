#include "DefaultMatrix.h"

#include "BaconBox/Core/Entity.h"
#include "BaconBox/Console.h"
#include "BaconBox/Helper/MathHelper.h"
#include "BaconBox/Components/Transform.h"
#include "BaconBox/Components/HasName.h"
#include "BaconBox/MovieClipEntity/MovieClipEntity.h"

namespace BaconBox {
	
	 

	DefaultMatrix::DefaultMatrix() : MatrixComponent(), entityContainer(NULL), matrix(), hasCustomMatrix(false) {
	    initializeConnections();
	}

	void DefaultMatrix::initializeConnections(){
	    this->addConnection(new ComponentConnection<EntityContainer>(&this->entityContainer));
	    MatrixComponent::initializeConnections();
	}
	
	void DefaultMatrix::receiveMessage(int senderID, int destID, int message, void *data) {
	    Component::receiveMessage(senderID, destID, message, data);
	    if(senderID == Transform::ID){
		if (message == Transform::MESSAGE_POSITION_CHANGED || message == Transform::MESSAGE_ROTATION_CHANGED || message == Transform::MESSAGE_SCALE_CHANGED) {
		    updateMatrix(transform->getPosition(), transform->getScale(), transform->getRotation());
		}
	    }
	}
	
	Matrix & DefaultMatrix::getMatrix(){
	    return matrix;
	}
	
		
	void DefaultMatrix::setFrameMatrix(int frame){
		if(hasCustomMatrix) return;
	    internalSetMatrix(matrixByParentFrame[frame]);
	}

	
	Matrix DefaultMatrix::getConcatMatrix(){
	    if(entityContainer && entityContainer->getParent()){
		MatrixComponent * matrixComponent  = reinterpret_cast<MatrixComponent*>(entityContainer->getParent()->getComponent(MatrixComponent::ID));
		Matrix temp = matrix;
		temp.concat(matrixComponent->getConcatMatrix());
		return temp;
	    }
	    else{
		return matrix;
	    }
	}

	
	
	void DefaultMatrix::updateMatrix(Vector2 position, Vector2 scale, float angle){
//	    if(matrix.isSkewed(scale.oldValue)){
//		throw; // TODO IMPLEMENT ME! This branch of the condition is broken.
//		matrix.rotate(-angle.oldValue);
//		matrix.translate(-position.oldValue);
//		matrix.scale(Vector2(1/scale.oldValue.x, 1/scale.oldValue.y));
//		
//		Matrix temp;
//		temp.scale(scale.newValue);
//		temp.translate(position.newValue);
//		temp.rotate(angle.newValue);
//		matrix = matrix * temp;
//		
//	    }
//	    else{
		float angleInRadian = -angle*MathHelper::AngleConvert<float>::DEGREES_TO_RADIANS;
		float cos  = MathHelper::cos(angleInRadian);
		float sin = MathHelper::sin(angleInRadian);
		matrix.a = scale.x * cos;
		matrix.c = scale.y * sin;
		matrix.b = scale.x *-sin;
		matrix.d = scale.y * cos;
		matrix.tx = position.x;
		matrix.ty = position.y;
		
		hasCustomMatrix = true;
//	    }
	}

void DefaultMatrix::internalSetMatrix(const Matrix & m){
	    MatrixComponent::setMatrix(m);
	   matrix = m;
	    Vector2 origin;
	    Vector2 width(1,0);
	    Vector2 height(0,1);
	    
	    
	    origin = m.multiplyWithVector(origin);
	    width = m.multiplyWithVector(width)- origin;
	    height = m.multiplyWithVector(height)-origin;
	    transform->setPosition(origin, false);
	    transform->setScale(Vector2(width.getLength(), height.getLength()), false);
	    transform->setRotation((width).getAngle()* -1 - 90, false);
	    
//	    this->matrix = m;
//	    Vector2 scale = transform->getScale();
//	    Vector2 position = transform->getPosition();
//	    float rotation = transform->getRotation();
//	    
//		rotation = MathHelper::asin(m.b/scale.x);
//		float cos = MathHelper::cos(rotation);
//		scale.x = m.a/cos;
//		scale.y = m.d/cos;
//		position.x = m.tx;
//		position.y = m.ty;
//		rotation *= MathHelper::AngleConvert<float>::RADIANS_TO_DEGREES; 
//		transform->setPosition(position, false);
//		transform->setScale(scale, false);
//		transform->setRotation(rotation, false);
	}
		    
	void DefaultMatrix::setMatrix(const Matrix & m){
	   internalSetMatrix(m);
		hasCustomMatrix = true;
	}
}