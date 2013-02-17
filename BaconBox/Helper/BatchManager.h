#ifndef BB_BATCH_MANAGER_H
#define BB_BATCH_MANAGER_H

#include "BaconBox/VertexArray.h"

namespace BaconBox {
	class BatchManager {
	public:
		BatchManager();
		
		BatchManager(const BatchManager &src);
		
		virtual ~BatchManager();
		
		BatchManager &operator=(const BatchManager &src);
	private:
	};
}

#endif /* defined(BB_BATCH_MANAGER_H) */

