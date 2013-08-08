/**
 * @file
 * @ingroup GraphicDrivers
 */
#ifndef BB_OPENGLDRIVER
#define BB_OPENGLDRIVER

#include "BaconBox/Display/Driver/GraphicDriver.h"
#include "BaconBox/Display/Driver/OpenGL/BBOpenGL.h"
#include "BaconBox/Display/DynamicBatch.h"
#include "BaconBox/Display/PixMap.h"

#include "GLSLProgram.h"
namespace BaconBox {
	/**
	 * OpenGl graphic driver.
	 * @ingroup GraphicDrivers
	 */
	class OpenGLDriver : public GraphicDriver {
		friend class BaseEngine;
	public:
		
		
		
		void renderToTexture(const TextureInformation *textureInformation, unsigned int viewportWidth = 0, unsigned int viewportHeight = 0, unsigned int contextWidth = 0, unsigned int contextHeight = 0);
		void endRenderToTexture();

		void drawShapeWithTextureColorColorOffset(const VertexArray &vertices,
												  const TextureInformation *textureInformation,
												  const TextureCoordinates &textureCoordinates,
												  const Color &color,
												  const Color &colorOffset, bool blend);
		
		void drawShapeWithTexture(const VertexArray &vertices,
							 const TextureInformation *textureInformation,
							 const TextureCoordinates &textureCoordinates,
							 bool blend);

		
		void drawBatchWithTexture(const VertexArray &vertices,
												  const TextureInformation *textureInformation,
												  const TextureCoordinates &textureCoordinates,
												  const IndiceArray &indices,
												  bool blend);


        void drawBatchWithTextureColorColorOffset(const VertexArray &vertices,
												  const TextureInformation *textureInformation,
												  const TextureCoordinates &textureCoordinates,
												  const IndiceArray &indices,
												  const ColorArray &colors,
												  const ColorArray &colorOffsets, bool blend);



		

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
		                  const Vector2 &zoom, const Color &backgroundColor, bool clearScreen);


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
		
		void scale(const Vector2 &scale);
		void rotate(float angle);
		
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
		bool shaderCompiled;
		bool  textureFBOInitialized;
		
		bool isRenderingToTexture;
		GLuint textureFBO;
		GLuint originalFramebuffer;

		
		void multMatrix(float *MatrixB,float MatrixA[16]);
		

		
		std::vector<float> tempTransformMatrix;
		std::vector<float> modelViewMatrix;
		std::vector<float> projectionMatrix;
		DynamicBatch batch;

        GLSLProgram *program;
       GLSLProgram *rgbProgram;
        GLSLProgram *alphaProgram;
		GLSLProgram *rgbNoTransformProgram;
		GLSLProgram * alphaNoTransformProgram;
		struct GPUState{
			GPUState():blend(true), textureID(-1),textureCoordinates(NULL),vertices(NULL),colors(NULL),colorOffsets(NULL), format(ColorFormat::NONE){}
			
			int textureID;
			bool blend;
			const GLfloat * textureCoordinates;
			const GLfloat * vertices;
			const GLfloat * colors;
			const GLfloat * colorOffsets;
			ColorFormat::type format;
			bool operator==(const GPUState &other) const {
				return (other.textureID == this->textureID) && (other.textureCoordinates == this->textureCoordinates) && (other.vertices == this->vertices) && (other.colors == this->colors) &&(other.colorOffsets == this->colorOffsets) && (other.format == this->format);
			}
			
			
		};
			
		GPUState currentGPUState;
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

		const TextureInformation *lastTexture;
		bool lastShapeBlend;
		
		bool lastShapeColorTransform;
		
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
