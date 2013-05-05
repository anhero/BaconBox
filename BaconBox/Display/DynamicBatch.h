#ifndef BB_DYNAMIC_BATCH_H
#define BB_DYNAMIC_BATCH_H

#include "BaconBox/StandardVertexArray.h"
#include "BaconBox/Display/Color.h"
#include "BaconBox/TextureCoordinates.h"
#include "BaconBox/Display/Driver/IndiceArray.h"
#include "BaconBox/Display/Driver/ColorArray.h"

namespace BaconBox {
	class GraphicDriver;
	struct TextureInformation;

	class DynamicBatch {
	public:
		DynamicBatch();

		~DynamicBatch();

		void prepareRender();

		void addItem(const VertexArray &newVertices, const Color &newColor, const TextureCoordinates &newTextureCoordinates);

		void render(GraphicDriver *driver, const TextureInformation *textureInformation);
		
		bool isSingle() const;
		
		const StandardVertexArray &getVertices() const;
		const TextureCoordinates &getTextureCoordinates() const;
		const Color &getColor() const;
	private:
		void refreshIndices();

		void initializeConnections();

		std::vector<VertexArray::SizeType> sizes;

		StandardVertexArray vertices;

		TextureCoordinates textureCoordinates;

		ColorArray colors;

		IndiceArray indices;

		IndiceArrayList indiceList;
	};
}

#endif /* defined(BB_DYNAMIC_BATCH_H) */

