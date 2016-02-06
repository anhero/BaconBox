#ifndef BB_DYNAMIC_BATCH_H
#define BB_DYNAMIC_BATCH_H

#include "BaconBox/StandardVertexArray.h"
#include "BaconBox/Display/Color.h"
#include "BaconBox/TextureCoordinates.h"
#include "BaconBox/Display/StandardRenderer/Driver/IndiceArray.h"
#include "BaconBox/Display/StandardRenderer/Driver/ColorArray.h"
#include "BaconBox/Display/StandardRenderer/Driver/ColorArray.h"


namespace BaconBox {
	class GraphicDriver;
	struct TextureInformation;

	class DynamicBatch {
	public:
		DynamicBatch();

		~DynamicBatch();

		/// Resets the state of the batch for a clean new batch.
		void prepareRender();
		
		/// Adds an item to the batch.
		void addItem(const VertexArray &newVertices,
					 const TextureCoordinates &newTextureCoordinates,
					 int degenerationStride = 4, int degenerationJump = -1);

		/// Color-aware item adding to the batch
		void addItem(const VertexArray &newVertices,
					 const Color &newColor, const Color &newColorOffset,
					 const TextureCoordinates &newTextureCoordinates,
					 int degenerationStride = 4, int degenerationJump = -1);

		/// Renders the current batch to the GraphicDriver.
		void render(GraphicDriver *driver, const TextureInformation *textureInformation, bool blend);

		// Unused?
		//bool isSingle() const;

		/// Gets the vertices for the current batch.
		const StandardVertexArray &getVertices() const;
		/// Gets the texture coordinates for the current batch.
		const TextureCoordinates &getTextureCoordinates() const;

		/// Gets the indices array for the current batch.
		const IndiceArray &getIndices() const;

		/// Gets the Color array for the current batch.
		const ColorArray &getColors() const;

		/// Gets the Color Offsets for the current batch.
		const ColorArray &getColorOffsets() const;

		/// Gets the color for the current batch, assuming a single color.
		const Color &getColor() const;

	private:
		void createNextIndices(int size, int degenerationStride, int degenerationJump);
		void refreshIndices();

		// Unused?
		//void initializeConnections();

		StandardVertexArray vertices;

		TextureCoordinates textureCoordinates;

		ColorArray colors;
        ColorArray colorOffsets;

		IndiceArray indices;
		IndiceArray::value_type indiceIterator;

	};
}

#endif /* defined(BB_DYNAMIC_BATCH_H) */

