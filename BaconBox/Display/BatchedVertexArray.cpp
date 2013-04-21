#include "BaconBox/Display/BatchedVertexArray.h"

#include <algorithm>

#include "BaconBox/Display/BatchManager.h"
#include "BaconBox/Console.h"

namespace BaconBox {
	BatchedVertexArray::BatchedVertexArray() : VertexArray(), vertices(new ContainerType()), batch(NULL), identifier(BatchManager::INVALID_ID) {
	}
	
	BatchedVertexArray::BatchedVertexArray(BatchManager *newBatch, SizeType nbVertices, ConstReference defaultValue) : VertexArray(), vertices(NULL), batch(newBatch), identifier(newBatch->addNewVertexArray(nbVertices, defaultValue)) {
	}
	
	BatchedVertexArray::BatchedVertexArray(SizeType nbVertices, ConstReference defaultValue) : VertexArray(), vertices(new ContainerType(nbVertices, defaultValue)), batch(NULL), identifier(BatchManager::INVALID_ID) {
	}
	
	BatchedVertexArray::BatchedVertexArray(size_t newIdentifier, BatchManager *newBatch) : VertexArray(), vertices(NULL), batch(newBatch), identifier(newIdentifier) {
	}
	
	BatchedVertexArray::BatchedVertexArray(const BatchedVertexArray &src) : VertexArray(src), vertices(new ContainerType(src.getNbVertices())), batch(NULL), identifier(BatchManager::INVALID_ID) {
		std::copy(src.getBegin(), src.getEnd(), this->getBegin());
	}
	
	BatchedVertexArray::~BatchedVertexArray() {
		// We delete our vertices if we're not associated with a batch.
		if (this->vertices) {
			delete this->vertices;
			this->vertices = NULL;
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
		this->setBatch(newBatch, BatchManager::INVALID_ID);
	}
	
	void BatchedVertexArray::setBatch(BatchManager *newBatch, size_t newIdentifier) {
		// We make sure the pointer we received is valid.
		if (newBatch) {
			// We make sure the new batch is different.
			if (newBatch != this->batch) {
				// We create a vertex array in the new batch if needed.
				if (newIdentifier == BatchManager::INVALID_ID) {
					newIdentifier = newBatch->addNewVertexArray(this->getNbVertices());
				}
				
				if (newBatch->containsVertexArray(newIdentifier)) {
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
				} else {
					Console::print("Unable to set the batch with the following idenfier: ");
					Console::println(newIdentifier);
				}
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
	
	size_t BatchedVertexArray::getIdentifier() const {
		return this->identifier;
	}
	
	void BatchedVertexArray::setIdentifier(size_t newIdentifier) {
		if (this->batch && this->identifier != newIdentifier && this->batch->containsVertexArray(newIdentifier)) {
			this->batch->resize(newIdentifier, this->getNbVertices());
			
			std::copy(this->getBegin(), this->getEnd(), this->batch->getBegin(newIdentifier));
			
			this->identifier = newIdentifier;
		}
	}
	
	VertexArray::Iterator BatchedVertexArray::getBegin() {
		if (this->batch) {
			return this->batch->getBegin(this->identifier);
		} else {
			return this->vertices->begin();
		}
	}
	
	VertexArray::ConstIterator BatchedVertexArray::getBegin() const {
		if (this->batch) {
			return this->batch->getConstBegin(this->identifier);
		} else {
			return this->vertices->begin();
		}
	}
	
	VertexArray::Iterator BatchedVertexArray::getEnd() {
		if (this->batch) {
			return this->batch->getEnd(this->identifier);
		} else {
			return this->vertices->end();
		}
	}
	
	VertexArray::ConstIterator BatchedVertexArray::getEnd() const {
		if (this->batch) {
			return this->batch->getConstEnd(this->identifier);
		} else {
			return this->vertices->end();
		}
	}
	
	VertexArray::ReverseIterator BatchedVertexArray::getReverseBegin() {
		if (this->batch) {
			return this->batch->getReverseBegin(this->identifier);
		} else {
			return this->vertices->rbegin();
		}
	}
	
	VertexArray::ConstReverseIterator BatchedVertexArray::getReverseBegin() const {
		if (this->batch) {
			return this->batch->getConstReverseBegin(this->identifier);
		} else {
			return this->vertices->rbegin();
		}
	}
	
	VertexArray::ReverseIterator BatchedVertexArray::getReverseEnd() {
		if (this->batch) {
			return this->batch->getReverseEnd(this->identifier);
		} else {
			return this->vertices->rend();
		}
	}
	
	VertexArray::ConstReverseIterator BatchedVertexArray::getReverseEnd() const {
		if (this->batch) {
			return this->batch->getConstReverseEnd(this->identifier);
		} else {
			return this->vertices->rend();
		}
	}
	
	bool BatchedVertexArray::isEmpty() const {
		if (this->batch) {
			return this->batch->isEmpty(this->identifier);
		} else {
			return this->vertices->empty();
		}
	}
	
	VertexArray::SizeType BatchedVertexArray::getNbVertices() const {
		if (this->batch) {
			return this->batch->getNbVertices(this->identifier);
		} else {
			return this->vertices->size();
		}
	}
	
	void BatchedVertexArray::clear() {
		if (this->batch) {
			this->batch->clear(this->identifier);
		} else {
			this->vertices->clear();
		}
	}
	
	VertexArray::Iterator BatchedVertexArray::insert(Iterator position, ConstReference value) {
		if (this->batch) {
			return this->batch->insert(this->identifier, position, value);
		} else {
			return this->vertices->insert(position, value);
		}
	}
	
	void BatchedVertexArray::insert(Iterator position, SizeType count, ConstReference value) {
		if (this->batch) {
			this->batch->insert(this->identifier, position, count, value);
		} else {
			this->vertices->insert(position, count, value);
		}
	}
	
	VertexArray::Iterator BatchedVertexArray::erase(Iterator position) {
		if (this->batch) {
			return this->batch->erase(this->identifier, position);
		} else {
			return this->vertices->erase(position);
		}
	}
	
	VertexArray::Iterator BatchedVertexArray::erase(Iterator first, Iterator last) {
		if (this->batch) {
			return this->batch->erase(this->identifier, first, last);
		} else {
			return this->vertices->erase(first, last);
		}
	}
	
	void BatchedVertexArray::pushBack(ConstReference newVertex) {
		if (this->batch) {
			this->batch->pushBack(this->identifier, newVertex);
		} else {
			this->vertices->push_back(newVertex);
		}
	}
	
	void BatchedVertexArray::popBack() {
		if (this->batch) {
			this->batch->popBack(this->identifier);
		} else {
			this->vertices->pop_back();
		}
	}
	
	void BatchedVertexArray::reset(size_t newIdentifier, BatchManager *newBatch) {
		if (this->vertices) {
			delete this->vertices;
			this->vertices = NULL;
		}
		
		this->batch = newBatch;
		this->identifier = newIdentifier;
	}
	
	void BatchedVertexArray::reset(SizeType nbVertices, ConstReference defaultValue) {
		if (this->vertices) {
			delete this->vertices;
		}
		
		this->batch = NULL;
		this->identifier = BatchManager::INVALID_ID;
		
		this->vertices = new ContainerType(nbVertices, defaultValue);
	}
	
	void BatchedVertexArray::removeFromBatch() {
		this->batch->removeVertexArray(this->identifier);
		this->batch = NULL;
		this->identifier = BatchManager::INVALID_ID;
	}
}
