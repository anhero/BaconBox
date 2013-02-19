#include "BaconBox/Helper/BatchedVertexArray.h"

#include <algorithm>

#include "BaconBox/Helper/BatchManager.h"

namespace BaconBox {
	BatchedVertexArray::BatchedVertexArray() : VertexArray(), vertices(new ContainerType()), batch(NULL), identifier(BatchManager::INVALID_ID) {
	}
	
	BatchedVertexArray::BatchedVertexArray(BatchManager *newBatch, SizeType nbVertices, ConstReference defaultValue) : VertexArray(), vertices(NULL), batch(newBatch), identifier(newBatch->addNewVertexArray(nbVertices, defaultValue)) {
	}
	
	BatchedVertexArray::BatchedVertexArray(SizeType nbVertices, ConstReference defaultValue) : VertexArray(), vertices(new ContainerType(nbVertices, defaultValue)), batch(NULL), identifier(BatchManager::INVALID_ID) {
	}
	
	BatchedVertexArray::BatchedVertexArray(const BatchedVertexArray &src) : VertexArray(src), vertices(new ContainerType(src.getNbVertices())), batch(NULL), identifier(BatchManager::INVALID_ID) {
		std::copy(src.getBegin(), src.getEnd(), this->getBegin());
	}
	
	BatchedVertexArray::~BatchedVertexArray() {
		// We delete our vertices if we're not associated with a batch.
		if (this->vertices) {
			delete this->vertices;
			this->vertices = NULL;
		} else if (this->batch) {
			// The vertex array is managed by a batch, we tell the batch to
			// remove the current instance's vertex array.
			this->removeFromBatch();
		}
	}
	
	BatchedVertexArray &BatchedVertexArray::operator=(const BatchedVertexArray &src) {
		if (this != &src) {
			this->resize(src.getNbVertices());
			std::copy(src.getBegin(), src.getEnd(), this->getBegin());
		}
		
		return *this;
	}
	
	BatchManager *BatchedVertexArray::getBatch() const {
		return this->batch;
	}
	
	void BatchedVertexArray::setBatch(BatchManager *newBatch) {
		// We make sure the pointer we received is valid.
		if (newBatch) {
			// We make sure the new batch is different.
			if (newBatch != this->batch) {
				// We create a vertex array in the new batch.
				int newIdentifier = newBatch->addNewVertexArray(this->getNbVertices());
				
				// We copy the current instance's contents to the new vertex
				// array.
				std::copy(this->getBegin(), this->getEnd(), newBatch->getBegin(newIdentifier));
				
				// If the current instance is not attached to another batch, we
				// delete the vertices.
				if (this->vertices) {
					delete this->vertices;
					this->vertices = NULL;
				}
				
				// We set the new batch.
				this->batch = newBatch;
				this->identifier = newIdentifier;
			}
		} else if (this->batch) {
			// If the pointer we received is null, we make sure the vertex
			// array is not part of a batch anymore.
			this->vertices = new ContainerType(this->getNbVertices());
			
			// We copy the batched vertex array's values to the new vertex array.
			std::copy(this->batch->getBegin(this->identifier), this->batch->getEnd(this->identifier), this->vertices->begin());
			
			// We remove the current instance from the batch.
			this->removeFromBatch();
		}
	}
	
	int BatchedVertexArray::getIdentifier() const {
		return this->identifier;
	}
	
	void BatchedVertexArray::removeFromBatch() {
		this->batch->removeVertexArray(this->identifier);
		this->batch = NULL;
		this->identifier = BatchManager::INVALID_ID;
	}
}
