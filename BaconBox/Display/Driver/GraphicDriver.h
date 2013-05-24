/**
 * @file
 * @ingroup GraphicDrivers
 */
#ifndef BB_GRAPHIC_DRIVER_H
#define BB_GRAPHIC_DRIVER_H

#include "BaconBox/Display/Driver/ColorArray.h"
#include "BaconBox/Display/Driver/ColorTransformArray.h"
#include "BaconBox/Display/Driver/IndiceArray.h"

#include "BaconBox/TextureCoordinates.h"

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
	class GraphicDriver {
		friend class BaseEngine;
	public:
		/**
		 * Gets the graphic driver instance.
		 * @return Reference to the graphic driver singleton.
		 */
		static GraphicDriver &getInstance();

		/**
		 * Draw a colored and textured shape with the given vertices, texture
		 * coordinate, rendering informations (colors array and texture) and
		 * number of vertices. Color information will blend with the texture
		 * (and background if alpha is not at max value of 255).
		 * @param vertices Vertices to draw.
		 * @param textureInformation Pointer to the texture information.
		 * @param textureCoordinates Texture coordinates in the texture to
		 * draw.
		 * @param color Color to render.
		 */
		virtual void drawShapeWithTextureAndColor(const VertexArray &vertices,
		                                          const TextureInformation *textureInformation,
		                                          const TextureCoordinates &textureCoordinates,
		                                          const Color &color) = 0;

        virtual void drawShapeWithTextureAndColorTransform(const VertexArray &vertices,
		                                          const TextureInformation *textureInformation,
		                                          const TextureCoordinates &textureCoordinates,
		                                          const Color &color,
		                                          const ColorTransformArray &colorMultiplier,
		                                          const ColorTransformArray &colorOffset) = 0;

//		/**
//		 * Draw a textured shape with the given vertices, texture coordinate,
//		 * rendering informations (colors array and textureID) and number of
//		 * vertices.
//		 * @param vertices Vertices to draw.
//		 * @param textureInformation Pointer to the texture information.
//		 * @param textureCoordinates Texture coordinates in the texture to
//		 * draw.
//		 */
//		virtual void drawShapeWithTexture(const VertexArray &vertices,
//		                                  const TextureInformation *textureInformation,
//		                                  const TextureCoordinates &textureCoordinates) = 0;
//
//		/**
//		 * Draws a colored shape.
//		 * @param vertices Vertices to draw.
//		 * @param color Color to render.
//		 */
//		virtual void drawShapeWithColor(const VertexArray &vertices,
//		                                const Color &color) = 0;



//		virtual void drawBatchWithTextureAndColor(const VertexArray &vertices,
//		                                          const TextureInformation *textureInformation,
//		                                          const TextureCoordinates &textureCoordinates,
//												  const IndiceArray &indices,
//												  const IndiceArrayList &indiceList,
//												  const ColorArray &colors) = 0;

        virtual void drawBatchWithTextureAndColorTransform(const VertexArray &vertices,
		                                  const TextureInformation *textureInformation,
		                                  const TextureCoordinates &textureCoordinates,
		                                  const IndiceArray &indices,
		                                  const IndiceArrayList &indiceList,
		                                  const ColorArray &colors,
		                                  const ColorTransformArray &colorMultipliers,
		                                  const ColorTransformArray &colorOffsets) = 0;

//		virtual void drawBatchWithTexture(const VertexArray &vertices,
//		                                  const TextureInformation *textureInformation,
//		                                  const TextureCoordinates &textureCoordinates,
//										  const IndiceArray &indices,
//										  const IndiceArrayList &indiceList) = 0;



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
		                          const Color &backgroundColor) = 0;


		virtual void initializeGraphicDriver();
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
		virtual TextureInformation *loadTexture(PixMap *pixMap);

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
