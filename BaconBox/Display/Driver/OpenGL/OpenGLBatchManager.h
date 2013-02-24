#ifndef BB_OpenGLBatchManager_H
#define BB_OpenGLBatchManager_H

#include <vector>

#include "BaconBox/Display/BatchManager.h"
#include "BaconBox/StandardVertexArray.h"
#include "BaconBox/TextureCoordinates.h"
#include "BaconBox/Display/Driver/IndiceArray.h"
#include "BaconBox/Display/Driver/ColorArray.h"

namespace BaconBox {
	class OpenGLBatchManager : public BatchManager {
	public:
		OpenGLBatchManager();
		
		OpenGLBatchManager(const OpenGLBatchManager &src);
		
		virtual ~OpenGLBatchManager();
		
		OpenGLBatchManager &operator=(const OpenGLBatchManager &src);
	private:
		std::vector<VertexArray::SizeType> indexes;
		
		StandardVertexArray vertices;
		
		TextureCoordinates textureCoordinates;
		
		ColorArray colors;
		
		IndiceArray indices;
		
		IndiceArrayList indiceList;
	};
}

#endif /* defined(BB_OpenGLBatchManager_H) */