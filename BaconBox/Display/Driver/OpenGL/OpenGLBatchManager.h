#ifndef BB_OpenGLBatchManager_H
#define BB_OpenGLBatchManager_H

#include "BaconBox/Display/BatchManager.h"

namespace BaconBox {
	class OpenGLBatchManager : public BatchManager {
	public:
		OpenGLBatchManager();
		
		OpenGLBatchManager(const OpenGLBatchManager &src);
		
		virtual ~OpenGLBatchManager();
		
		OpenGLBatchManager &operator=(const OpenGLBatchManager &src);
	private:
	};
}

#endif /* defined(BB_OpenGLBatchManager_H) */

