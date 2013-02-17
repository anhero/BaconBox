#ifndef BB_BatchedVertexArray_H
#define BB_BatchedVertexArray_H

#include "BaconBox/VertexArray.h"

namespace BaconBox {
	class BatchManager;
	
	/**
	 * Base class for all batched vertex array implementations.
	 */
	class BatchedVertexArray : public VertexArray {
	public:
		/**
		 * Initializes an empty batched vertex array without any batch
		 * associated to it.
		 */
		BatchedVertexArray();
		
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
	};
}

#endif /* defined(BB_BatchedVertexArray_H) */

