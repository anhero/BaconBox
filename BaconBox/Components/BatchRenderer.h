#ifndef BB_BATCH_RENDERER_H
#define BB_BATCH_RENDERER_H

#include <vector>

#include "BaconBox/Core/Component.h"
#include "BaconBox/StandardVertexArray.h"
#include "BaconBox/Display/Color.h"
#include "BaconBox/TextureCoordinates.h"
#include "BaconBox/Display/Driver/IndiceArray.h"
#include "BaconBox/Display/Driver/ColorArray.h"

namespace BaconBox {
	class BatchRenderer : public Component {
	public:
		BB_ID_HEADER;
		
		BatchRenderer();
		
		BatchRenderer(const BatchRenderer &src);
		
		virtual ~BatchRenderer();
		
		BatchRenderer &operator=(const BatchRenderer &src);
		
		virtual BatchRenderer *clone() const;
		
		virtual void receiveMessage(int senderID, int destID, int message, void *data);
		
		void prepareRender();
		
		void addItem(const VertexArray &newVertices, const Color &newColor, const TextureCoordinates &newTextureCoordinates);
		
		void renderBatch();
	private:
		void refreshIndices();
		
		std::vector<VertexArray::SizeType> sizes;
		
		StandardVertexArray vertices;
		
		TextureCoordinates textureCoordinates;
		
		ColorArray colors;
		
		IndiceArray indices;
		
		IndiceArrayList indiceList;
	};
}

#endif /* defined(BB_BATCH_RENDERER_H) */

