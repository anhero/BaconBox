#include "BaconBox/Helper/BatchedVertexArray.h"

namespace BaconBox {
	BatchedVertexArray::BatchedVertexArray() : VertexArray() {
	}
	
	BatchedVertexArray::BatchedVertexArray(const BatchedVertexArray &src) : VertexArray(src) {
	}
	
	BatchedVertexArray::~BatchedVertexArray() {
	}
	
	BatchedVertexArray &BatchedVertexArray::operator=(const BatchedVertexArray &src) {
		if (this != &src) {
		}
		
		return *this;
	}
}
