#include "MatrixComponent.h"
#include "BaconBox/Components/Transform.h"
namespace BaconBox {
	BB_ID_IMPL(MatrixComponent);

	int MatrixComponent::MESSAGE_MATRIX_CHANGED = IDManager::generateID();


	MatrixComponent::MatrixComponent(): Component(), transform(NULL){
	    initializeConnections();
	}


	void MatrixComponent::initializeConnections() {
		// We add the connections.
		this->addConnection(new ComponentConnection<Transform>(&this->transform));
		this->refreshConnections();
	}

	void MatrixComponent::setMatrix(const Matrix2D & m){
	    Matrix2D temp = m;
	    sendMessage(Entity::BROADCAST, MESSAGE_MATRIX_CHANGED, &temp);
	}


	    MatrixComponentProxy::MatrixComponentProxy(Entity *entity) : ComponentProxy(entity, NULL) {

	    }

	    void MatrixComponentProxy::setMatrix(const Matrix2D & m){
		 reinterpret_cast<MatrixComponent*>(component)->setMatrix(m);
	    }

	    Matrix2D & MatrixComponentProxy::getMatrix(){
		 return reinterpret_cast<MatrixComponent*>(component)->getMatrix();
	    }

	    Matrix2D MatrixComponentProxy::getConcatMatrix(){
		 return reinterpret_cast<MatrixComponent*>(component)->getConcatMatrix();
	    }


        MatrixComponent * MatrixComponentProxy::getMatrixComponent(){
            return reinterpret_cast<MatrixComponent*>(component);
        }

	    void MatrixComponentProxy::setMatrixComponent(MatrixComponent * matrixComponent){
		component = matrixComponent;
		entity->addComponent(matrixComponent);
	    }


}
