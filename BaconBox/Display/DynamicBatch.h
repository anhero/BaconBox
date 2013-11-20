#ifndef BB_DYNAMIC_BATCH_H
#define BB_DYNAMIC_BATCH_H

#include "BaconBox/StandardVertexArray.h"
#include "BaconBox/Display/Color.h"
#include "BaconBox/TextureCoordinates.h"
#include "BaconBox/Display/Driver/IndiceArray.h"
#include "BaconBox/Display/Driver/ColorArray.h"
#include "BaconBox/Display/Driver/ColorArray.h"


namespace BaconBox {
	class GraphicDriver;
	struct TextureInformation;

	class DynamicBatch {
	public:
		DynamicBatch();

		~DynamicBatch();

		void prepareRender();
		
		void addItem(const VertexArray &newVertices, const TextureCoordinates &newTextureCoordinates, int degenerationStride = 4, int degenerationJump = -1);

		void addItem(const VertexArray &newVertices, const Color &newColor,
					 const Color &newColorOffset, const TextureCoordinates &newTextureCoordinates, int degenerationStride = 4, int degenerationJump = -1);

		void render(GraphicDriver *driver, const TextureInformation *textureInformation, bool blend);

		bool isSingle() const;

		const StandardVertexArray &getVertices() const;
		const TextureCoordinates &getTextureCoordinates() const;
		const Color &getColor() const;
	private:
		
		void createNextIndices(int size, int degenerationStride, int degenerationJump);
		
		void refreshIndices();

		void initializeConnections();


		StandardVertexArray vertices;

		TextureCoordinates textureCoordinates;

		ColorArray colors;
        ColorArray colorOffsets;
		IndiceArray indices;

		IndiceArray::value_type indiceIterator;

	};
}

#endif /* defined(BB_DYNAMIC_BATCH_H) */

