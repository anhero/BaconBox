#ifndef BB_BatchedVertexArray_H
#define BB_BatchedVertexArray_H

#include "BaconBox/VertexArray.h"

namespace BaconBox {
	class BatchManager;
	
	/**
	 * Represents a vertex array whose vertices are in a batch
	 * manager.
	 */
	class BatchedVertexArray : public VertexArray {
	public:
		/**
		 * Initializes an empty batched vertex array without any batch
		 * associated to it.
		 */
		BatchedVertexArray();
		
		/**
		 * Initializes a new batched vertex array with the specified batch.
		 * @param newBegin Index of the first vertex in the batch.
		 * @param newNbVertices Number of vertices in the vertex array.
		 * @param newBatch Pointer to the batch that manages the vertices.
		 */
		BatchedVertexArray(SizeType newBegin, SizeType newNbVertices, BatchManager *newBatch);
		
		/**
		 * Initializes a copy of another batched vertex array. The
		 * copy does not have any parent batch.
		 * @param src Batched vertex array to create a copy of.
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
		 */
		BatchedVertexArray &operator=(const BatchedVertexArray &src);
		
		/**
		 * Gets the iterator pointing to the first vertex.
		 * @return Iterator pointing to the first vertex in the array.
		 */
		virtual Iterator getBegin();
		
		/**
		 * Gets the constant iterator pointing to the first vertex.
		 * @return Const iterator pointing to the first vertex in the array.
		 */
		virtual ConstIterator getBegin() const;
		
		/**
		 * Gets the iterator pointing to the end of the array (after the last
		 * vertex.
		 * @return Iterator pointing to the end of the array.
		 */
		virtual Iterator getEnd();
		
		/**
		 * Gets the constant iterator pointing to the end of the array (after
		 * the last vertex).
		 * @return Const iterator pointing to the end of the array.
		 */
		virtual ConstIterator getEnd() const;
		
		/**
		 * Gets the reverse iterator pointing to the first vertex.
		 * @return Reverse iterator pointing to the first vertex in the array.
		 */
		virtual ReverseIterator getReverseBegin();
		
		/**
		 * Gets the constant reverse iterator pointing to the first vertex.
		 * @return Const reverse iterator pointing to the first vertex in the
		 * array.
		 */
		virtual ConstReverseIterator getReverseBegin() const;
		
		/**
		 * Gets the reverse iterator pointing to the end of the array (after the
		 * last vertex, or before the first vertex because it's in reverse).
		 * @return Reverse terator pointing to the end of the array.
		 */
		virtual ReverseIterator getReverseEnd();
		
		/**
		 * Gets the constant reverse iterator pointing to the end of the array
		 * (after the last vertex, or before the first vertex because it's
		 * in reverse).
		 * @return Const reverse iterator pointing to the end of the array.
		 */
		virtual ConstReverseIterator getReverseEnd() const;
		
		/**
		 * Checks if the array is empty or not.
		 * @return True if the array is empty, false if not.
		 */
		virtual bool isEmpty() const;
		
		/**
		 * Gets the array of vertices' size.
		 * @return Number of vertices the array contains.
		 */
		virtual SizeType getNbVertices() const;
		
		/**
		 * Erases all the vertices.
		 */
		virtual void clear();
		
		/**
		 * Inserts a vertex in the array.
		 * @param position The new vertex will be inserted before this position.
		 * @param value Value to insert.
		 * @return Iterator pointing to the vertex following the inserted
		 * vertex.
		 */
		virtual Iterator insert(Iterator position, ConstReference value = ValueType());
		
		/**
		 * Inserts vertices in the array.
		 * @param position The new vertices will be inserted before this
		 * position.
		 * @param count Number of vertices to insert.
		 * @param value Value to insert.
		 */
		virtual void insert(Iterator position, SizeType count, ConstReference value = ValueType());
		
		/**
		 * Erases the specified vertex.
		 * @param position Iterator pointing to the vertex to erase.
		 * @return Iterator pointing to the vertex following the one erased.
		 */
		virtual Iterator erase(Iterator position);
		
		/**
		 * Erases a bunch of vertices.
		 * @param first First vertex to erase.
		 * @param last Last vertex to erase.
		 * @return Iterator pointing to the vertex following the last one
		 * erased.
		 */
		virtual Iterator erase(Iterator first, Iterator last);
		
		/**
		 * Inserts a vertex at the end of the array.
		 * @param newVertex Vertex to insert at the end of the array.
		 */
		virtual void pushBack(ConstReference newVertex);
		
		/**
		 * Erases the last vertex in the array.
		 */
		virtual void popBack();
		
		/**
		 * Resizes the array and fills up the newly created vertices with the
		 * one given.
		 * @param count New array's size.
		 * @param value Value to insert if the new size is bigger.
		 */
		virtual void resize(SizeType count, ConstReference value = ValueType());
	private:
		
		/// Index in the batch where the vertices begin.
		SizeType begin;
		
		/// Number of vertices.
		SizeType nbVertices;
		
		/// Pointer to the parent batch.
		BatchManager *batch;
		
		/// Pointer to the temporary array of vertices.
		ContainerType *vertices;
	};
}

#endif /* defined(BB_BatchedVertexArray_H) */

