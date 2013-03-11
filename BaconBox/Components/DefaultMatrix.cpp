#include "DefaultMatrix.h"

#include "BaconBox/Core/Entity.h"
#include "BaconBox/Console.h"
#include "BaconBox/Helper/MathHelper.h"
#include "BaconBox/Components/Transform.h"
namespace BaconBox {
	
	 

	DefaultMatrix::DefaultMatrix() : MatrixComponent(), entityContainer(NULL), matrix() {
	}

	
	
	void DefaultMatrix::receiveMessage(int senderID, int destID, int message, void *data) {
	    if(senderID == Transform::ID){
		if (message == Transform::MESSAGE_POSITION_CHANGED || message == Transform::MESSAGE_ROTATION_CHANGED || message == Transform::MESSAGE_SCALE_CHANGED) {
		    updateMatrix(transform->getPosition(), transform->getScale(), transform->getRotation());
		}
	    }
	}
	
	Matrix & DefaultMatrix::getMatrix(){
	    return matrix;
	}
	
	Matrix & DefaultMatrix::getConcatMatrix(){
	    return matrix;
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
		matrix.a = scale.x * cos;
		matrix.c = scale.y * MathHelper::sin(angleInRadian);
		matrix.b = scale.x *-matrix.c;
		matrix.d = scale.y * cos;
		matrix.tx = position.x;
		matrix.ty = position.y;
//	    }
	}

	
	void DefaultMatrix::setMatrix(const Matrix & m){
	    MatrixComponent::setMatrix(m);
	    this->matrix = m;
	    Vector2 scale = transform->getScale();
	    Vector2 position = transform->getPosition();
	    float rotation = transform->getRotation();
	    
		rotation = MathHelper::asin(m.b/scale.x);
		float cos = MathHelper::cos(rotation);
		scale.x = m.a/cos;
		scale.y = m.d/cos;
		position.x = m.tx;
		position.y = m.ty;
		rotation *= MathHelper::AngleConvert<float>::RADIANS_TO_DEGREES; 
		transform->setPosition(position, false);
		transform->setScale(scale, false);
		transform->setRotation(rotation, false);
	}
}