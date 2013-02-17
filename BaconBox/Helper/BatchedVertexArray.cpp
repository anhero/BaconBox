#include "BatchedVertexArray.h"

#include <algorithm>

#include "BaconBox/Helper/BatchManager.h"

namespace BaconBox {
	BatchedVertexArray::BatchedVertexArray() : VertexArray(), begin(0), nbVertices(0), batch(NULL), vertices(NULL) {
	}

	BatchedVertexArray::BatchedVertexArray(SizeType newBegin, SizeType newNbVertices, BatchManager *newBatch) : VertexArray(), begin(newBegin), nbVertices(newNbVertices), batch(newBatch), vertices(NULL) {
	}
	
	BatchedVertexArray::BatchedVertexArray(const BatchedVertexArray &src) : VertexArray(src), begin(0), nbVertices(src.nbVertices), batch(NULL), vertices(new ContainerType(src.nbVertices)) {
		std::copy(src.getBegin(), src.getEnd(), this->vertices->begin());
	}
	
	BatchedVertexArray::~BatchedVertexArray() {
		if (vertices) {
			delete vertices;
			vertices = NULL;
		}
	}
	
	BatchedVertexArray &BatchedVertexArray::operator=(const BatchedVertexArray &src) {
		if (this != &src) {
			this->resize(src.getNbVertices());
			
			std::copy(src.getBegin(), src.getEnd(), this->getBegin());
		}
		
		return *this;
	}
}
