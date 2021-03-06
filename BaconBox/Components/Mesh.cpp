#include "Mesh.h"
#include "BaconBox/Core/IDManager.h"
#include "BaconBox/Components/Transform.h"
#include "BaconBox/Core/Entity.h"
#include "BaconBox/Helper/Vector2ChangedData.h"
#include "BaconBox/Helper/ValueChangedData.h"
#include "BaconBox/Components/ComponentConnection.h"
#include "BaconBox/Display/Window/MainWindow.h"
namespace BaconBox {
	BB_ID_IMPL(Mesh);

	Mesh::Mesh() : Component(), mustSync(true), transform(NULL), postTransformVertices(4), matrixComponent(NULL){
		this->initializeConnections();
	}



	StandardVertexArray &Mesh::getPreTransformVertices(){
		mustSync = true;
		return preTransformVertices;
	}

	StandardVertexArray &Mesh::getPostTransformVertices(){
	    if(true || mustSync)syncMesh();
	    return postTransformVertices;
	}

//	const StandardVertexArray Mesh::getRelativeVertices() const {
//		Transform *transform = reinterpret_cast<Transform*>(this->getEntity()->getComponent(Transform::ID));
//
//		if (transform) {
//			StandardVertexArray result(this->vertices);
//
//			Vector2 position = transform->getPosition();
//
//			result.move(-position.x, -position.y);
//
//			return result;
//		} else {
//			return StandardVertexArray();
//		}
//	}
	void Mesh::resize(int size){
		preTransformVertices.resize(size);
		postTransformVertices.resize(size);
	}
	
	void Mesh::initializeConnections() {
		// We add the connections.
		this->addConnection(new ComponentConnection<Transform>(&this->transform));
		this->addConnection(new ComponentConnection<MatrixComponent>(&this->matrixComponent));
		this->refreshConnections();
	}

	void Mesh::syncMesh(){
		mustSync = false;

		// First, resize as needed.
		if (preTransformVertices.getNbVertices() != postTransformVertices.getNbVertices()) {
			postTransformVertices.resize(preTransformVertices.getNbVertices());
		}
		
		// Sync all positions
		for(int i = 0; i < preTransformVertices.getNbVertices(); i++){
			postTransformVertices[i] = preTransformVertices[i];
		}

		// Apply the transformation
		if (matrixComponent) {
			postTransformVertices.multiplyWithMatrix(matrixComponent->getConcatMatrix());
		}
	}


	void Mesh::receiveMessage(int senderID, int destID, int message, void *data) {
	    Component::receiveMessage(senderID, destID, message, data);
		if (senderID == Transform::ID && destID == Entity::BROADCAST) {
			if (message == Transform::MESSAGE_POSITION_CHANGED) {
			    	mustSync = true;
//				Vector2ChangedData newPosition(*reinterpret_cast<Vector2ChangedData *>(data));
//
//				this->postTransformVertices.move(newPosition.newValue.x - newPosition.oldValue.x, newPosition.newValue.y - newPosition.oldValue.y);
			} else if (message == Transform::MESSAGE_ROTATION_CHANGED) {
				mustSync = true;
//				ValueChangedData<float> newRotation(*reinterpret_cast<ValueChangedData<float> *>(data));
//
//				Transform *transform = reinterpret_cast<Transform*>(this->getEntity()->getComponent(Transform::ID));
//
//				if (transform) {
//					this->postTransformVertices.rotateFromPoint(newRotation.newValue - newRotation.oldValue, transform->getPosition());
//				}
			} else if (message == Transform::MESSAGE_SCALE_CHANGED) {
			    mustSync = true;
//				Vector2ChangedData newScale(*reinterpret_cast<Vector2ChangedData *>(data));
//
//				Transform *transform = reinterpret_cast<Transform*>(this->getEntity()->getComponent(Transform::ID));
//
//				if (transform) {
//					this->postTransformVertices.scaleFromPoint(newScale.newValue.x / newScale.oldValue.x, newScale.newValue.y / newScale.oldValue.y, transform->getPosition());
//				}
			}
			else if (message == MatrixComponent::MESSAGE_MATRIX_CHANGED) {
			    mustSync = true;
			}
		}


	}
}
