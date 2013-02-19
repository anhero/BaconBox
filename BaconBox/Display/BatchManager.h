#ifndef BB_BATCH_MANAGER_H
#define BB_BATCH_MANAGER_H

#include "BaconBox/VertexArray.h"

namespace BaconBox {
	/**
	 * Base class for all batch manager implementations.
	 */
	class BatchManager {
		friend class BatchedVertexArray;
	public:
		static const int INVALID_ID = -1;
		
		BatchManager();
		
		BatchManager(const BatchManager &src);
		
		virtual ~BatchManager();
		
		BatchManager &operator=(const BatchManager &src);
		
	protected:
		/**
		 * Adds a new batched vertex array.
		 * @param nbVertices Number of vertices to add to the batch.
		 * @param defaultValue Value to set to the new vertices.
		 * @return Unique identifier for the new vertex array.
		 */
		virtual int addNewVertexArray(VertexArray::SizeType nbVertices, VertexArray::ConstReference defaultValue = VertexArray::ValueType()) = 0;
		
		/**
		 * Adds a new batched array from a list of vertices.
		 * @param newVertices New vertices to copy in the batch.
		 * @return Unique identifier for the new vertex array.
		 */
		virtual int addNewVertexArray(const VertexArray::ContainerType &newVertices) = 0;
		
		/**
		 * Removes a vertex array from the batch.
		 * @param identifier Unique identifier of the vertex array to remove.
		 */
		virtual bool removeVertexArray(int identifier);
		
		/**
		 * Gets the iterator pointing to the first vertex.
		 * @return Iterator pointing to the first vertex in the array.
		 */
		virtual VertexArray::Iterator getBegin(int identifier) = 0;
		
		/**
		 * Gets the constant iterator pointing to the first vertex.
		 * @return Const iterator pointing to the first vertex in the array.
		 */
		virtual VertexArray::ConstIterator getConstBegin(int identifier) const = 0;
		
		/**
		 * Gets the iterator pointing to the end of the array (after the last
		 * vertex.
		 * @return Iterator pointing to the end of the array.
		 */
		virtual VertexArray::Iterator getEnd(int identifier) = 0;
		
		/**
		 * Gets the constant iterator pointing to the end of the array (after
		 * the last vertex).
		 * @return Const iterator pointing to the end of the array.
		 */
		virtual VertexArray::ConstIterator getConstEnd(int identifier) const = 0;
		
		/**
		 * Gets the reverse iterator pointing to the first vertex.
		 * @return Reverse iterator pointing to the first vertex in the array.
		 */
		virtual VertexArray::ReverseIterator getReverseBegin(int identifier) = 0;
		
		/**
		 * Gets the constant reverse iterator pointing to the first vertex.
		 * @return Const reverse iterator pointing to the first vertex in the
		 * array.
		 */
		virtual VertexArray::ConstReverseIterator getConstReverseBegin(int identifier) const = 0;
		
		/**
		 * Gets the reverse iterator pointing to the end of the array (after the
		 * last vertex, or before the first vertex because it's in reverse).
		 * @return Reverse terator pointing to the end of the array.
		 */
		virtual VertexArray::ReverseIterator getReverseEnd(int identifier) = 0;
		
		/**
		 * Gets the constant reverse iterator pointing to the end of the array
		 * (after the last vertex, or before the first vertex because it's
		 * in reverse).
		 * @return Const reverse iterator pointing to the end of the array.
		 */
		virtual VertexArray::ConstReverseIterator getConstReverseEnd(int identifier) const = 0;
		
		/**
		 * Checks if the array is empty or not.
		 * @return True if the array is empty, false if not.
		 */
		virtual bool isEmpty(int identifier) const = 0;
		
		/**
		 * Gets the array of vertices' size.
		 * @return Number of vertices the array contains.
		 */
		virtual VertexArray::SizeType getNbVertices(int identifier) const = 0;
		
		/**
		 * Erases all the vertices.
		 */
		virtual void clear(int identifier) = 0;
		
		/**
		 * Inserts a vertex in the array.
		 * @param position The new vertex will be inserted before this position.
		 * @param value Value to insert.
		 * @return Iterator pointing to the vertex following the inserted
		 * vertex.
		 */
		virtual VertexArray::Iterator insert(int identifier, VertexArray::Iterator position, VertexArray::ConstReference value = VertexArray::ValueType()) = 0;
		
		/**
		 * Inserts vertices in the array.
		 * @param position The new vertices will be inserted before this
		 * position.
		 * @param count Number of vertices to insert.
		 * @param value Value to insert.
		 */
		virtual void insert(int identifier, VertexArray::Iterator position, VertexArray::SizeType count, VertexArray::ConstReference value = VertexArray::ValueType()) = 0;
		
		/**
		 * Erases the specified vertex.
		 * @param position Iterator pointing to the vertex to erase.
		 * @return Iterator pointing to the vertex following the one erased.
		 */
		virtual VertexArray::Iterator erase(int identifier, VertexArray::Iterator position) = 0;
		
		/**
		 * Erases a bunch of vertices.
		 * @param first First vertex to erase.
		 * @param last Last vertex to erase.
		 * @return Iterator pointing to the vertex following the last one
		 * erased.
		 */
		virtual VertexArray::Iterator erase(int identifier, VertexArray::Iterator first, VertexArray::Iterator last) = 0;
		
		/**
		 * Inserts a vertex at the end of the array.
		 * @param newVertex Vertex to insert at the end of the array.
		 */
		virtual void pushBack(int identifier, VertexArray::ConstReference newVertex) = 0;
		
		/**
		 * Erases the last vertex in the array.
		 */
		virtual void popBack(int identifier) = 0;
		
		/**
		 * Resizes the array and fills up the newly created vertices with the
		 * one given.
		 * @param count New array's size.
		 * @param value Value to insert if the new size is bigger.
		 */
		virtual void resize(int identifier, VertexArray::SizeType count, VertexArray::ConstReference value = VertexArray::ValueType()) = 0;
	private:
	};
}

#endif /* defined(BB_BATCH_MANAGER_H) */

