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
		BatchManager();
		
		BatchManager(const BatchManager &src);
		
		virtual ~BatchManager();
		
		BatchManager &operator=(const BatchManager &src);
		
	protected:
		virtual VertexArray::Iterator getIterator(VertexArray::SizeType index) = 0;
		
		virtual VertexArray::ConstIterator getConstIterator(VertexArray::SizeType index) const = 0;
		
		virtual VertexArray::ReverseIterator getReverseIterator(VertexArray::SizeType reverseIndex) = 0;
		
		virtual VertexArray::ConstReverseIterator getConstReverseIterator(VertexArray::SizeType reverseIndex) const = 0;
		
		virtual VertexArray::Iterator insert(VertexArray::Iterator position, VertexArray::ConstReference value = VertexArray::ValueType()) = 0;
		
		virtual void insert(VertexArray::Iterator position, VertexArray::SizeType count, VertexArray::ConstReference value = VertexArray::ValueType()) = 0;
		
		virtual VertexArray::Iterator erase(VertexArray::Iterator position) = 0;
		
		virtual VertexArray::Iterator erase(VertexArray::Iterator first, VertexArray::Iterator last) = 0;
	private:
	};
}

#endif /* defined(BB_BATCH_MANAGER_H) */

