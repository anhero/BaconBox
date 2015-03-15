/**
 * @file
 * @ingroup GraphicDrivers
 */
#ifndef BB_OPENGLDRIVER
#define BB_OPENGLDRIVER

#include "BaconBox/Display/StandardRenderer/Driver/GraphicDriver.h"
#include "BaconBox/Display/StandardRenderer/Driver/OpenGL/BBOpenGL.h"
#include "BaconBox/Display/DynamicBatch.h"
#include "BaconBox/Display/PixMap.h"

#include "GLSLProgram.h"
#include "BaconBox/Core/Singleton.h"

namespace BaconBox {
	/**
	 * OpenGl graphic driver.
	 * @ingroup GraphicDrivers
	 */
	class OpenGLDriver : public GraphicDriver {
		friend class GraphicDriver;
		BB_SINGLETON_DECL(OpenGLDriver);

	public:
		void renderToTexture(const TextureInformation *textureInformation,
							 unsigned int viewportWidth = 0,
							 unsigned int viewportHeight = 0,
							 unsigned int contextWidth = 0,
							 unsigned int contextHeight = 0);

		void endRenderToTexture();

		void drawShapeWithTextureColorColorOffset(const VertexArray &vertices,
												  const TextureInformation *textureInformation,
												  const TextureCoordinates &textureCoordinates,
												  const Color &color,
												  const Color &colorOffset, bool blend, int degenerationStride, int degenerationJump);

		void drawShapeWithTexture(const VertexArray &vertices,
								  const TextureInformation *textureInformation,
								  const TextureCoordinates &textureCoordinates,
								  bool blend, int degenerationStride, int degenerationJump);

		void drawShapeWithColorColorOffset(const VertexArray &vertices,
										   const Color &color,
										   const Color &colorOffset,
										   bool blend, int degenerationStride, int degenerationJump);

		/// Handles drawing a batch with whatever methods needed.
		void drawBatch(const DynamicBatch *batch, const TextureInformation *texInfo, const bool blend);

		/**
		 * Prepare the scene before rendering object.
		 * It clears the draw buffer and resets the transformation matrix with the given
		 * parameters.
		 * @param position Shift the matrix using this 2D vector.
		 * @param angle Apply a rotation to the matrix in degree.
		 * @param zoom Apply a scale factor to the matrix. 1 is unchanged, less than 1 zoom out,
		 * more than 1 zoom in.
		 * @param backgroundColor The scene's background color.
		 */
		void prepareScene(const Vector2 &position, float angle,
						  const Vector2 &zoom, const Color &backgroundColor, bool clearScreen);

		void initializeGraphicDriver();
		void tearGraphicDriver();
		void resetProjection();

		/**
		 * Applies a translation on the current matrix.
		 * @param translation 2D translation to apply.
		 */
		void translate(const Vector2 &translation);

		void scale(const Vector2 &scale);

		void rotate(float angle);

		/**
		 * Loads the identity matrix as the current matrix.
		 */
		void loadIdentity();

		/**
		 * Pushes the current matrix on the stack.
		 */
		void pushMatrix();

		/**
		 * Pops the current matrix from the stack.
		 */
		void popMatrix();

		/**
		 * Load a texture into graphic memory.
		 * @param pixMap A pixmap object containing the buffer the driver must load.
		 */
		TextureInformation *loadTexture(PixMap *pixMap, TextureInformation *textureInfo = NULL);

		/**
		 *  Remove a texture from graphic memory
		 */
		void deleteTexture(TextureInformation *textureInfo);

		/**
		 * Finalizes all pending batches if there are any.
		 */
		void finalizeRender();

	private:

		/// Common behaviour between draw__() functions.
		void internalDrawShape(const VertexArray &vertices,
							   const TextureInformation *textureInformation, const TextureCoordinates &textureCoordinates,
							   bool blend, int degenerationStride, int degenerationJump,
							   bool colorTransform = false);

		bool shaderCompiled;
		bool textureFBOInitialized;

		/// Whether we're rendering to a texture
		bool isRenderingToTexture;
		/// Framebuffer for rendering to texture
		GLuint textureFBO;
		/// Reference to the main framebuffer.
		GLuint originalFramebuffer;

		void multMatrix(float *MatrixB,float MatrixA[16]);

		std::vector<float> tempTransformMatrix;
		std::vector<float> modelViewMatrix;
		std::vector<float> projectionMatrix;
		DynamicBatch batch;

		/// Current GLSL Program used
		GLSLProgram *program;

		GLSLProgram *rgbProgram;
		GLSLProgram *rgbWithoutTextureProgram;
		GLSLProgram *alphaProgram;
		GLSLProgram *rgbNoTransformProgram;
		GLSLProgram *alphaNoTransformProgram;

		/// Representation of the GPU state.
		struct GPUState{
			GPUState() : blend(true),
						 textureID(0),
						 textureCoordinates(NULL),
						 vertices(NULL),
						 colors(NULL),
						 colorOffsets(NULL),
						 format(ColorFormat::NONE)
			{}

			/// OpenGL Texture ID
			GLuint textureID;
			/// Whether we blend
			bool blend;
			/// List of texture coordinates for each vertices.
			const GLfloat * textureCoordinates;
			/// List of vertices
			const GLfloat * vertices;
			/// List of vertex colors
			const GLfloat * colors;
			/// List of vertex color offsets
			const GLfloat * colorOffsets;
			/// Current color format
			ColorFormat::type format;

			/// Checks for equivalent states
			bool operator==(const GPUState &other) const {
				return (other.textureID == this->textureID) &&
					   (other.textureCoordinates == this->textureCoordinates) &&
					   (other.vertices == this->vertices) &&
					   (other.colors == this->colors) &&
					   (other.colorOffsets == this->colorOffsets) &&
					   (other.format == this->format);
			}
		};

		/// State of the GPU to be used as next `lastGPUState`.
		GPUState currentGPUState;
		/// State of the GPU last time a `draw*` function was called.
		GPUState lastGPUState;
		
		struct attributes{
			GLuint vertices;
			GLuint texCoord;
			GLuint color;
			GLuint colorOffset;
			attributes(){
				vertices = 0;
				texCoord = 1;
				color = 2;
				colorOffset = 3;
			}
		} attributes;
		
		
		struct{
			GLuint tex;
			GLuint projection;
			GLuint modelView;
		} uniforms;

		/// Reference to the last texture used.
		const TextureInformation *lastTexture;

		/// Whether the last shape was rendered blended.
		bool lastShapeBlend;
		
		/// Whether the last shape had a color transform.
		bool lastShapeColorTransform;

		// Used to represent informations when no texture is applied.
		TextureInformation *noTexture;

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
