#ifndef BB_BATCH_MANAGER_H
#define BB_BATCH_MANAGER_H

#include <cstddef>

#include "BaconBox/VertexArray.h"
#include "BaconBox/TextureCoordinates.h"

namespace BaconBox {
	class Color;
	
	/**
	 * Base class for all batch manager implementations.
	 */
	class BatchManager {
	public:
		static const size_t INVALID_ID;
		
		BatchManager();
		
		BatchManager(const BatchManager &src);
		
		virtual ~BatchManager();
		
		BatchManager &operator=(const BatchManager &src);
		
		/**
		 * Sets the color for a given vertex array.
		 * @param color Color to set to all of the vertex array's vertices.
		 * @param identifier Unique identifier of the vertex array.
		 */
		virtual void setColor(const Color &color, size_t identifier) = 0;
		
		/**
		 * Sets the texture coordinates for a given vertex array.
		 * @param textureCoordinates Texture coordinates to copy. There must be
		 * as many texture coordinates as there are vertices. The number of
		 * texture coordinates copied is equal to
		 * min(src.size(), getNbVertices(identifier)).
		 * @param identifier Unique identifier of the vertex array.
		 */
		virtual void setTextureCoordinates(const TextureCoordinates &textureCoordinates, size_t identifier) = 0;
		
		/**
		 * Adds a new batched vertex array.
		 * @param nbVertices Number of vertices to add to the batch.
		 * @param defaultValue Value to set to the new vertices.
		 * @return Unique identifier for the new vertex array.
		 */
		virtual size_t addNewVertexArray(VertexArray::SizeType nbVertices, VertexArray::ConstReference defaultValue = VertexArray::ValueType()) = 0;
		
		/**
		 * Adds a new batched array from a list of vertices.
		 * @param newVertices New vertices to copy in the batch.
		 * @return Unique identifier for the new vertex array.
		 */
		virtual size_t addNewVertexArray(const VertexArray::ContainerType &newVertices) = 0;
		
		/**
		 * Removes a vertex array from the batch.
		 * @param identifier Unique identifier of the vertex array to remove.
		 */
		virtual void removeVertexArray(size_t identifier) = 0;
		
		/**
		 * Checks whether or not the batch contains an array with the given
		 * identifier.
		 * *param identifier Unique identifier of the vertex array to check
		 * the existence of.
		 */
		virtual bool containsVertexArray(size_t identifier) const = 0;
		
		/**
		 * Gets the iterator pointing to the first vertex.
		 * @return Iterator pointing to the first vertex in the array.
		 */
		virtual VertexArray::Iterator getBegin(size_t identifier) = 0;
		
		/**
		 * Gets the constant iterator pointing to the first vertex.
		 * @return Const iterator pointing to the first vertex in the array.
		 */
		virtual VertexArray::ConstIterator getConstBegin(size_t identifier) const = 0;
		
		/**
		 * Gets the iterator pointing to the end of the array (after the last
		 * vertex.
		 * @return Iterator pointing to the end of the array.
		 */
		virtual VertexArray::Iterator getEnd(size_t identifier) = 0;
		
		/**
		 * Gets the constant iterator pointing to the end of the array (after
		 * the last vertex).
		 * @return Const iterator pointing to the end of the array.
		 */
		virtual VertexArray::ConstIterator getConstEnd(size_t identifier) const = 0;
		
		/**
		 * Gets the reverse iterator pointing to the first vertex.
		 * @return Reverse iterator pointing to the first vertex in the array.
		 */
		virtual VertexArray::ReverseIterator getReverseBegin(size_t identifier) = 0;
		
		/**
		 * Gets the constant reverse iterator pointing to the first vertex.
		 * @return Const reverse iterator pointing to the first vertex in the
		 * array.
		 */
		virtual VertexArray::ConstReverseIterator getConstReverseBegin(size_t identifier) const = 0;
		
		/**
		 * Gets the reverse iterator pointing to the end of the array (after the
		 * last vertex, or before the first vertex because it's in reverse).
		 * @return Reverse terator pointing to the end of the array.
		 */
		virtual VertexArray::ReverseIterator getReverseEnd(size_t identifier) = 0;
		
		/**
		 * Gets the constant reverse iterator pointing to the end of the array
		 * (after the last vertex, or before the first vertex because it's
		 * in reverse).
		 * @return Const reverse iterator pointing to the end of the array.
		 */
		virtual VertexArray::ConstReverseIterator getConstReverseEnd(size_t identifier) const = 0;
		
		/**
		 * Checks if the array is empty or not.
		 * @return True if the array is empty, false if not.
		 */
		virtual bool isEmpty(size_t identifier) const = 0;
		
		/**
		 * Gets the array of vertices' size.
		 * @return Number of vertices the array contains.
		 */
		virtual VertexArray::SizeType getNbVertices(size_t identifier) const = 0;
		
		/**
		 * Erases all the vertices.
		 */
		virtual void clear(size_t identifier) = 0;
		
		/**
		 * Inserts a vertex in the array.
		 * @param position The new vertex will be inserted before this position.
		 * @param value Value to insert.
		 * @return Iterator pointing to the vertex following the inserted
		 * vertex.
		 */
		virtual VertexArray::Iterator insert(size_t identifier, VertexArray::Iterator position, VertexArray::ConstReference value = VertexArray::ValueType()) = 0;
		
		/**
		 * Inserts vertices in the array.
		 * @param position The new vertices will be inserted before this
		 * position.
		 * @param count Number of vertices to insert.
		 * @param value Value to insert.
		 */
		virtual void insert(size_t identifier, VertexArray::Iterator position, VertexArray::SizeType count, VertexArray::ConstReference value = VertexArray::ValueType()) = 0;
		
		/**
		 * Erases the specified vertex.
		 * @param position Iterator pointing to the vertex to erase.
		 * @return Iterator pointing to the vertex following the one erased.
		 */
		virtual VertexArray::Iterator erase(size_t identifier, VertexArray::Iterator position) = 0;
		
		/**
		 * Erases a bunch of vertices.
		 * @param first First vertex to erase.
		 * @param last Last vertex to erase.
		 * @return Iterator pointing to the vertex following the last one
		 * erased.
		 */
		virtual VertexArray::Iterator erase(size_t identifier, VertexArray::Iterator first, VertexArray::Iterator last) = 0;
		
		/**
		 * Inserts a vertex at the end of the array.
		 * @param newVertex Vertex to insert at the end of the array.
		 */
		virtual void pushBack(size_t identifier, VertexArray::ConstReference newVertex) = 0;
		
		/**
		 * Erases the last vertex in the array.
		 */
		virtual void popBack(size_t identifier) = 0;
		
		/**
		 * Resizes the array and fills up the newly created vertices with the
		 * one given.
		 * @param count New array's size.
		 * @param value Value to insert if the new size is bigger.
		 */
		virtual void resize(size_t identifier, VertexArray::SizeType count, VertexArray::ConstReference value = VertexArray::ValueType()) = 0;
	private:
	};
}

#endif /* defined(BB_BATCH_MANAGER_H) */

