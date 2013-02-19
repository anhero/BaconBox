#include "BaconBox/Helper/BatchedVertexArray.h"

#include <algorithm>

#include "BaconBox/Helper/BatchManager.h"

namespace BaconBox {
	BatchedVertexArray::BatchedVertexArray() : VertexArray(), vertices(new ContainerType()), batch(NULL), identifier(BatchManager::INVALID_ID) {
	}
	
	BatchedVertexArray::BatchedVertexArray(const BatchedVertexArray &src) : VertexArray(src), vertices(new ContainerType(src.getNbVertices())), batch(NULL), identifier(BatchManager::INVALID_ID) {
		std::copy(src.getBegin(), src.getEnd(), this->vertices->begin());
	}
	
	BatchedVertexArray::~BatchedVertexArray() {
		if (this->vertices) {
			delete this->vertices;
			this->vertices = NULL;
		} else if (this->batch) {
			this->batch->removeVertexArray(this->identifier);
			this->batch = NULL;
			this->identifier = BatchManager::INVALID_ID;
		}
	}
	
	BatchedVertexArray &BatchedVertexArray::operator=(const BatchedVertexArray &src) {
		if (this != &src) {
			
		}
		
		return *this;
	}
}
