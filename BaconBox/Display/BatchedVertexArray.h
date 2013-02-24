#ifndef BB_BatchedVertexArray_H
#define BB_BatchedVertexArray_H

#include "BaconBox/VertexArray.h"

namespace BaconBox {
	class BatchManager;
	
	/**
	 * Represents a vertex array that can be managed by a BatchManager.
	 * @see BaconBox::BatchManager
	 */
	class BatchedVertexArray : public VertexArray {
		friend class BatchManager;
	public:
		/**
		 * Initializes an empty batched vertex array without any batch
		 * associated to it.
		 */
		BatchedVertexArray();
		
		/**
		 * Initializes a new BatchedVertexArray with the given number of
		 * vertices set to the given default value.
		 * @param newBatch Pointer to the batch that should manage this array.
		 * @param nbVertices Number of vertices the new instance should have.
		 * @param defaultValue Value to use for the new vertices.
		 */
		BatchedVertexArray(BatchManager *newBatch, SizeType nbVertices, ConstReference defaultValue = ValueType());
		
		/**
		 * Initializes a new BatchedVertexArray with the given number of
		 * vertices set to the given default value.
		 * @param nbVertices Number of vertices the new instance should have.
		 * @param defaultValue Value to use for the new vertices.
		 */
		explicit BatchedVertexArray(SizeType nbVertices, ConstReference defaultValue = ValueType());
		
		/**
		 * Initializes a new BatchedVertexArray with the given identifier and 
		 * BatchManager.
		 * @param newIdentifier Existing identifier to use.
		 * @param newBatch Pointer to the batch that manages this array.
		 */
		BatchedVertexArray(size_t newIdentifier, BatchManager *newBatch);
		
		/**
		 * Initializes a copy of another batched vertex array. The
		 * copy does not have any parent batch.
		 * @param src BatchedVertexArray to create a copy of.
		 */
		BatchedVertexArray(const BatchedVertexArray &src);
		
		/**
		 * Removes itself from its parent batch and makes sure all
		 * memory used is freed.
		 */
		~BatchedVertexArray();
		
		/**
		 * Copies the given batched vertex array's vertices into
		 * the current instance.
		 * @param src BatchedVertexArray to copy.
		 * @return Reference to the current instance.
		 */
		BatchedVertexArray &operator=(const BatchedVertexArray &src);
		
		/**
		 * Gets a pointer to the batch managing the current instance.
		 * @return Pointer to the batch managing the current instance if it has
		 * one; otherwise NULL.
		 * @see BaconBox::BatchedVertexArray::batch
		 */
		BatchManager *getBatch() const;
		
		/**
		 * Sets the batch the current instance will be managed by.
		 * @param newBatch Pointer to the current instance's new batch.
		 * @see BaconBox::BatchedVertexArray::batch
		 */
		void setBatch(BatchManager *newBatch);

		/**
		 * Sets the batch the current instance will be managed by.
		 * @param newBatch Pointer to the current instance's new batch.
		 * @param newIdentifier Existing unique identifier to use. If the
		 * value contains BaconBox::BatchManager::INVALID_ID, asks the
		 * batch for a new identifier.
		 * @see BaconBox::BatchedVertexArray::batch
		 * @see BaconBox::BatchedVertexArray::identifier
		 */
		void setBatch(BatchManager *newBatch, size_t newIdentifier);

		/**
		 * Gets the unique identifier used by the current instance's batch.
		 * @return Unique identifier used to identify the vertex array in the
		 * batch if it has one; otherwise -1.
		 * @see BaconBox::BatchedVertexArray::identifier
		 */
		size_t getIdentifier() const;
		
		/**
		 * Sets the unique identifier. The instance must be associated with a
		 * batch and the unique identifier must exist, otherwise nothing is done.
		 * @param newIdentifier New unique idenfier to use.
		 */
		void setIdentifier(size_t newIdentifier);
		
		/**
		 * Gets the iterator pointing to the first vertex.
		 * @return Iterator pointing to the first vertex in the array.
		 */
		Iterator getBegin();
		
		/**
		 * Gets the constant iterator pointing to the first vertex.
		 * @return Const iterator pointing to the first vertex in the array.
		 */
		ConstIterator getBegin() const;
		
		/**
		 * Gets the iterator pointing to the end of the array (after the last
		 * vertex.
		 * @return Iterator pointing to the end of the array.
		 */
		Iterator getEnd();
		
		/**
		 * Gets the constant iterator pointing to the end of the array (after
		 * the last vertex).
		 * @return Const iterator pointing to the end of the array.
		 */
		ConstIterator getEnd() const;
		
		/**
		 * Gets the reverse iterator pointing to the first vertex.
		 * @return Reverse iterator pointing to the first vertex in the array.
		 */
		ReverseIterator getReverseBegin();
		
		/**
		 * Gets the constant reverse iterator pointing to the first vertex.
		 * @return Const reverse iterator pointing to the first vertex in the
		 * array.
		 */
		ConstReverseIterator getReverseBegin() const;
		
		/**
		 * Gets the reverse iterator pointing to the end of the array (after the
		 * last vertex, or before the first vertex because it's in reverse).
		 * @return Reverse terator pointing to the end of the array.
		 */
		ReverseIterator getReverseEnd();
		
		/**
		 * Gets the constant reverse iterator pointing to the end of the array
		 * (after the last vertex, or before the first vertex because it's
		 * in reverse).
		 * @return Const reverse iterator pointing to the end of the array.
		 */
		ConstReverseIterator getReverseEnd() const;
		
		/**
		 * Checks if the array is empty or not.
		 * @return True if the array is empty, false if not.
		 */
		bool isEmpty() const;
		
		/**
		 * Gets the array of vertices' size.
		 * @return Number of vertices the array contains.
		 */
		SizeType getNbVertices() const;
		
		/**
		 * Erases all the vertices.
		 */
		void clear();
		
		/**
		 * Inserts a vertex in the array.
		 * @param position The new vertex will be inserted before this position.
		 * @param value Value to insert.
		 * @return Iterator pointing to the vertex following the inserted
		 * vertex.
		 */
		Iterator insert(Iterator position, ConstReference value = ValueType());
		
		/**
		 * Inserts vertices in the array.
		 * @param position The new vertices will be inserted before this
		 * position.
		 * @param count Number of vertices to insert.
		 * @param value Value to insert.
		 */
		void insert(Iterator position, SizeType count, ConstReference value = ValueType());
		
		/**
		 * Erases the specified vertex.
		 * @param position Iterator pointing to the vertex to erase.
		 * @return Iterator pointing to the vertex following the one erased.
		 */
		Iterator erase(Iterator position);
		
		/**
		 * Erases a bunch of vertices.
		 * @param first First vertex to erase.
		 * @param last Last vertex to erase.
		 * @return Iterator pointing to the vertex following the last one
		 * erased.
		 */
		Iterator erase(Iterator first, Iterator last);
		
		/**
		 * Inserts a vertex at the end of the array.
		 * @param newVertex Vertex to insert at the end of the array.
		 */
		void pushBack(ConstReference newVertex);
		
		/**
		 * Erases the last vertex in the array.
		 */
		void popBack();
		
		/**
		 * Resizes the array and fills up the newly created vertices with the
		 * one given.
		 * @param count New array's size.
		 * @param value Value to insert if the new size is bigger.
		 */
		void resize(SizeType count, ConstReference value = ValueType());
		
		/**
		 * Sets a new unique idenfier and a new batch without copying the
		 * current instance's vertices.
		 * @param newIdentifier New unique idenfier to use.
		 * @param newBatch Pointer to the new batch manager to use.
		 */
		void reset(size_t newIdentifier, BatchManager *newBatch);
		
		/**
		 * Unlinks the current instance from a batch (if linked) or clears
		 * the current instance's vertices if not linked with any batches and
		 * initializes a new vertex array with the given parameters.
		 * @param nbVertices Number of vertices.
		 * @param defaultValue Value to use to initialize the vertices.
		 */
		void reset(SizeType nbVertices, ConstReference defaultValue = ValueType());
	private:
		void removeFromBatch();
		
		/**
		 * Pointer to the current instance's vertices. Used only if the current
		 * instance does not have a batch. Set to NULL when the array has a
		 * batch.
		 */
		ContainerType *vertices;
		
		/**
		 * Pointer to the batch managing the array. Null if the array is not
		 * managed by any batch.
		 */
		BatchManager *batch;
		
		/**
		 * Unique identifier used to identify the array in its batch. -1 if the
		 * array isn't managed by any batch.
		 */
		size_t identifier;
	};
}

#endif /* defined(BB_BatchedVertexArray_H) */

