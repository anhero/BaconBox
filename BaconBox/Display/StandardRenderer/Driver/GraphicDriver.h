/**
 * @file
 * @ingroup GraphicDrivers
 */
#ifndef BB_GRAPHIC_DRIVER_H
#define BB_GRAPHIC_DRIVER_H

#include "BaconBox/PlatformFlagger.h"
#include "BaconBox/Display/StandardRenderer/Driver/ColorArray.h"
#include "BaconBox/Display/StandardRenderer/Driver/IndiceArray.h"

#include "BaconBox/TextureCoordinates.h"

#include "BaconBox/Core/Singleton.h"

#include "BaconBox/Display/DynamicBatch.h"

namespace BaconBox {
	class VertexArray;
	struct TextureInformation;
	class Color;
	class PixMap;
	/**
	 * Graphic abstraction layer.
	 * A driver must handle rendering and loading (into graphic memory) of
	 * bitmap data.
	 * @class GraphicDriver
	 * @ingroup Driver
	 */
	class GraphicDriver : public Singleton {
		friend class BaseEngine;
	public:
		/**
		 * Gets the graphic driver instance.
		 * @return Reference to the graphic driver singleton.
		 */
		static GraphicDriver &getInstance();
		
		virtual void renderToTexture(const TextureInformation *textureInformation, unsigned int viewportWidth = 0, unsigned int viewportHeight = 0, unsigned int contextWidth = 0, unsigned int contextHeight = 0) = 0;
		virtual void endRenderToTexture() = 0;


		virtual void drawShapeWithTexture(const VertexArray &vertices,
								  const TextureInformation *textureInformation,
								  const TextureCoordinates &textureCoordinates,
								  bool blend, int degenerationStride, int degenerationJump) = 0;
		
		
        virtual void drawShapeWithTextureColorColorOffset(const VertexArray &vertices,
														  const TextureInformation *textureInformation,
														  const TextureCoordinates &textureCoordinates,
														  const Color &color,
														  const Color &colorOffset, bool blend, int degenerationStride, int degenerationJump) = 0;

        virtual void drawShapeWithColorColorOffset(const VertexArray &vertices,
                                                   const Color &color,
                                                   const Color &colorOffset,
                                                   bool blend, int degenerationStride, int degenerationJump) = 0;

		/// Handles drawing a batch with whatever methods needed.
		virtual void drawBatch(const DynamicBatch *batch, const TextureInformation *texInfo, const bool blend) = 0;

		virtual void resetProjection() = 0;

		/**
		 * Prepare the scene before rendering object.
		 * It clear the draw buffer and reset the transformation matrix with the given
		 * parameters.
		 * @param position Shift the matrix using this 2D vector.
		 * @param angle Apply a rotation to the matrix in degree.
		 * @param zoom Apply a scale factor to the matrix. 1 is unchanged, less than 1 zoom out,
		 * more than 1 zoom in.
		 * @param backgroundColor The scene's background color.
		 */
		virtual void prepareScene(const Vector2 &position, float angle,
		                          const Vector2 &zoom,
		                          const Color &backgroundColor, bool clearScreen) = 0;


		virtual void initializeGraphicDriver();
		virtual void tearGraphicDriver() = 0;

		virtual bool isInitialized();
		/**
		 * Pushes the current matrix on the stack.
		 */
		virtual void pushMatrix() = 0;

		/**
		 * Applies a translation on the current matrix.
		 * @param translation 2D translation to apply.
		 */
		virtual void translate(const Vector2 &translation) = 0;
		virtual void scale(const Vector2 &scale) = 0;
		virtual void rotate(float angle) = 0;
		
		

		/**
		 * Loads the identity matrix as the current matrix.
		 */
		virtual void loadIdentity() = 0;

		/**
		 * Pops the current matrix from the stack.
		 */
		virtual void popMatrix() = 0;

		/**
		 * Load a texture into graphic memory.
		 * @param pixMap A pixmap object containing the buffer the driver must load.
		 */
		virtual TextureInformation *loadTexture(PixMap *pixMap, TextureInformation *textureInfo = NULL);

        /**
         *  Remove a texture from graphic memory
         */
        virtual void deleteTexture(TextureInformation * textureInfo) = 0;

		/**
		 * Finalizes all pending batches if there are any.
		 */
		virtual void finalizeRender() = 0;

	protected:

		 bool initialized;
		/**
		 * Default constructor.
		 */
		GraphicDriver();

		/**
		 * Destructor.
		 */
		virtual ~GraphicDriver();

	};

}

#endif
