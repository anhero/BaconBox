/**
 * @file
 * @ingroup GraphicDrivers
 */
#ifndef BB_OPENGLDRIVER
#define BB_OPENGLDRIVER

#include "BaconBox/Display/Driver/GraphicDriver.h"
#include "BaconBox/Display/Driver/OpenGL/BBOpenGL.h"
#include "BaconBox/Display/DynamicBatch.h"
#include "GLSLProgram.h"
namespace BaconBox {
	/**
	 * OpenGl graphic driver.
	 * @ingroup GraphicDrivers
	 */
	class OpenGLDriver : public GraphicDriver {
		friend class BaseEngine;
	public:
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
		void drawShapeWithTextureAndColor(const VertexArray &vertices,
		                                  const TextureInformation *textureInformation,
		                                  const TextureCoordinates &textureCoordinates,
		                                  const Color &color);


        void drawShapeWithTextureAndColorTransform(const VertexArray &vertices,
                  const TextureInformation *textureInformation,
                  const TextureCoordinates &textureCoordinates,
                  const Color &color,
                  const ColorTransformArray &colorMultiplier,
                  const ColorTransformArray &colorOffset);
		/**
		 * Draw a textured shape with the given vertices, texture coordinate,
		 * rendering informations (colors array and textureID) and number of
		 * vertices.
		 * @param vertices Vertices to draw.
		 * @param textureInformation Pointer to the texture information.
		 * @param textureCoordinates Texture coordinates in the texture to
		 * draw.
		 */
		void drawShapeWithTexture(const VertexArray &vertices,
		                          const TextureInformation *textureInformation,
		                          const TextureCoordinates &textureCoordinates);
		/**
		 * Draws a colored shape.
		 * @param vertices Vertices to draw.
		 * @param color Color to render.
		 */
		void drawShapeWithColor(const VertexArray &vertices,
		                        const Color &color);


		void drawBatchWithTextureAndColor(const VertexArray &vertices,
		                                  const TextureInformation *textureInformation,
		                                  const TextureCoordinates &textureCoordinates,
		                                  const IndiceArray &indices,
		                                  const IndiceArrayList &indiceList,
		                                  const ColorArray &colors);

        void drawBatchWithTextureAndColorTransform(const VertexArray &vertices,
		                                  const TextureInformation *textureInformation,
		                                  const TextureCoordinates &textureCoordinates,
		                                  const IndiceArray &indices,
		                                  const IndiceArrayList &indiceList,
		                                  const ColorArray &colors,
		                                  const ColorTransformArray &colorMultipliers,
		                                  const ColorTransformArray &colorOffsets);




		void drawBatchWithTexture(const VertexArray &vertices,
		                          const TextureInformation *textureInformation,
		                          const TextureCoordinates &textureCoordinates,
		                          const IndiceArray &indices,
		                          const IndiceArrayList &indiceList);



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
		void prepareScene(const Vector2 &position, float angle,
		                  const Vector2 &zoom, const Color &backgroundColor);


		void initializeGraphicDriver();

		/**
		 * Pushes the current matrix on the stack.
		 */
		void pushMatrix();

		/**
		 * Applies a translation on the current matrix.
		 * @param translation 2D translation to apply.
		 */
		void translate(const Vector2 &translation);

		/**
		 * Loads the identity matrix as the current matrix.
		 */
		void loadIdentity();

		/**
		 * Pops the current matrix from the stack.
		 */
		void popMatrix();

		/**
		 * Load a texture into graphic memory.
		 * @param pixMap A pixmap object containing the buffer the driver must load.
		 */
		TextureInformation *loadTexture(PixMap *pixMap);

		/**
		 *  Remove a texture from graphic memory
		 */
		void deleteTexture(TextureInformation *textureInfo);

		/**
		 * Finalizes all pending batches if there are any.
		 */
		void finalizeRender();
	private:
		static float clampColorComponent(unsigned short component);

		void internalDrawShapeWithTextureAndColor(const VertexArray &vertices,
		                                          const TextureInformation *textureInformation,
		                                          const TextureCoordinates &textureCoordinates,
		                                          const Color &color);

        void internalDrawShapeWithTextureAndColorTransform(const VertexArray &vertices,
		                                          const TextureInformation *textureInformation,
		                                          const TextureCoordinates &textureCoordinates,
		                                          const Color &color,
		                                          const ColorTransformArray &colorMultiplier,
		                                          const ColorTransformArray &colorOffset);

		DynamicBatch batch;

        GLSLProgram *program;
        GLuint locColorMultiplier;
        GLuint locColorOffset;

		const TextureInformation *lastTexture;

		/**
		 * Default constructor.
		 */
		OpenGLDriver();

		/**
		 * Destructor.
		 */
		~OpenGLDriver();
	};
}

#endif
