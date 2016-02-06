#include "BaconBox/Display/StandardRenderer/Driver/OpenGL/OpenGLDriver.h"

#include <stdint.h>

#include "BaconBox/PlatformFlagger.h"
#include "BaconBox/Display/TextureInformation.h"
#include "BaconBox/Helper/MathHelper.h"
#include "BaconBox/Display/Window/MainWindow.h"
#include "BaconBox/VertexArray.h"
#include "BaconBox/Display/Color.h"
#include "BaconBox/Console.h"
#include "BaconBox/ResourceManager.h"
#include "BaconBox/Core/Engine.h"

#define GET_PTR(vertices) reinterpret_cast<const GLfloat *>(&(*vertices.getBegin()))
#define GET_TEX_PTR(textureCoordinates) reinterpret_cast<const GLfloat *>(&(*textureCoordinates.begin()))
#define GET_PTR_BATCH(vertices, adjustment) reinterpret_cast<const GLfloat *>(&(*(vertices.getBegin() + adjustment)))
#define GET_TEX_PTR_BATCH(textureCoordinates, adjustment) reinterpret_cast<const GLfloat *>(&(*(textureCoordinates.begin() + adjustment)))


namespace BaconBox {

	BB_SINGLETON_IMPL(OpenGLDriver)

	void OpenGLDriver::drawShapeWithTextureColorColorOffset(const VertexArray &vertices,
															const TextureInformation *textureInformation,
															const TextureCoordinates &textureCoordinates,
															const Color &color,
															const Color &colorOffset,
															bool blend, int degenerationStride, int degenerationJump){
		internalDrawShape(vertices, textureInformation, textureCoordinates,
						  blend, degenerationStride, degenerationJump, true);
		this->batch.addItem(vertices, color, colorOffset, textureCoordinates, degenerationStride, degenerationJump);
	}

	void OpenGLDriver::drawShapeWithTexture(const VertexArray &vertices,
											const TextureInformation *textureInformation,
											const TextureCoordinates &textureCoordinates,
											bool blend, int degenerationStride, int degenerationJump) {
		internalDrawShape(vertices, textureInformation, textureCoordinates,
						  blend, degenerationStride, degenerationJump);
		this->batch.addItem(vertices, textureCoordinates, degenerationStride, degenerationJump);
	}

	void OpenGLDriver::drawShapeWithColorColorOffset(const VertexArray &vertices,
													 const Color &color,
													 const Color &colorOffset,
													 bool blend, int degenerationStride, int degenerationJump) {

		TextureCoordinates textureCoordinates;
		internalDrawShape(vertices, noTexture, textureCoordinates,
						  blend, degenerationStride, degenerationJump, true);
		this->batch.addItem(vertices, color, colorOffset, textureCoordinates, degenerationStride, degenerationJump);
	}

	void OpenGLDriver::internalDrawShape(const VertexArray &vertices,
										 const TextureInformation *textureInformation, const TextureCoordinates &textureCoordinates,
										 bool blend, int degenerationStride, int degenerationJump,
										 bool colorTransform) {
		if (this->lastTexture){
			if(textureInformation != this->lastTexture || blend != lastShapeBlend || colorTransform != lastShapeColorTransform) {
				this->batch.render(this, this->lastTexture, lastShapeBlend);
				this->batch.prepareRender();
			}
		}
		else{
			this->batch.prepareRender();
		}
		this->lastTexture = textureInformation;
		lastShapeBlend = blend;
		lastShapeColorTransform = colorTransform;
	}

	void OpenGLDriver::drawBatch(const DynamicBatch *batch, const TextureInformation *textureInformation, const bool blend) {

		const IndiceArray &indices = batch->getIndices();

		// Whether we need color transforms
		bool withColorTransforms = ( batch->getColors().size() > 0 );

		// Sets up the new states
		currentGPUState.textureID = textureInformation->textureId;
		currentGPUState.textureCoordinates = GET_TEX_PTR_BATCH(batch->getTextureCoordinates(), 0);
		currentGPUState.vertices = GET_PTR_BATCH(batch->getVertices(), 0);
		currentGPUState.format = textureInformation->colorFormat;
		currentGPUState.blend = blend;

		if (withColorTransforms) {
			currentGPUState.colors = GET_TEX_PTR_BATCH(batch->getColors(), 0);
			currentGPUState.colorOffsets = GET_TEX_PTR_BATCH(batch->getColorOffsets(), 0);
		}

		// Shader program handling
		{
			// First, handle selecting the right program.

			// Default programs, without color transforms
			GLSLProgram *localRGBA  = rgbNoTransformProgram;
			GLSLProgram *localAlpha = alphaNoTransformProgram;

			// If we need the color transforms, select those programs
			if (withColorTransforms) {
				localRGBA = rgbProgram;
				localAlpha = alphaProgram;
			}
			// When there's no texture
			if (textureInformation->textureId == 0) {
				localRGBA = rgbWithoutTextureProgram;
				// We do not have a alphaProgram for those...
				// It is assumed that a textureless shape is ColorFormat::RGBA
			}

			// Check whether we need to change and reset the programs
			bool wrongProgramType = (program != localRGBA && program != localAlpha);
			// Whether the program needs to change
			bool programChanging = ((currentGPUState.format != lastGPUState.format) || wrongProgramType);

			if (programChanging) {
				// Prepare the vertex attributes
				if (wrongProgramType) {
					if (withColorTransforms) {
						glEnableVertexAttribArray(attributes.colorOffset);
						glEnableVertexAttribArray(attributes.color);
					}
					else {
						glDisableVertexAttribArray(attributes.colorOffset);
						glDisableVertexAttribArray(attributes.color);
					}
				}

				// Choose the appropriate program
				if (textureInformation->colorFormat == ColorFormat::ALPHA) {
					program = localAlpha;
				}
				else {
					program = localRGBA;
				}

				// Lastly, prepare the program for use.
				program->use();
				program->sendUniform(uniforms.tex, 0);
				program->sendUniform(uniforms.projection, &(projectionMatrix[0]));
				program->sendUniform(uniforms.modelView, &(modelViewMatrix[0]));

			}
		}

		// Synchronizing states.

		if (lastGPUState.blend != currentGPUState.blend) {
			if (blend) { glEnable(GL_BLEND); }
			else { glDisable(GL_BLEND); }
		}

		if (currentGPUState.textureID != lastGPUState.textureID) {
			glBindTexture(GL_TEXTURE_2D, currentGPUState.textureID);
		}
		if (currentGPUState.textureCoordinates != lastGPUState.textureCoordinates) {
			glVertexAttribPointer(attributes.texCoord, 2, GL_FLOAT, GL_FALSE, 0, currentGPUState.textureCoordinates);
		}
		if (currentGPUState.vertices != lastGPUState.vertices) {
			glVertexAttribPointer(attributes.vertices, 2, GL_FLOAT, GL_FALSE, 0, currentGPUState.vertices);
		}
		if (currentGPUState.colors != lastGPUState.colors) {
			glVertexAttribPointer(attributes.color,    4, GL_FLOAT, GL_FALSE, 0, currentGPUState.colors);
		}
		if (currentGPUState.colorOffsets != lastGPUState.colorOffsets) {
			glVertexAttribPointer(attributes.colorOffset, 4, GL_FLOAT, GL_FALSE, 0, currentGPUState.colorOffsets);
		}

		lastGPUState = currentGPUState;

		// Drawing the batch.
		glDrawElements(GL_TRIANGLE_STRIP, indices.size(), GL_UNSIGNED_SHORT, &(indices[0]));

	}

	void OpenGLDriver::prepareScene(const Vector2 &position, float angle,
	                                const Vector2 &zoom,
	                                const Color &backgroundColor, bool clearScreen) {
		
		if(clearScreen){
		glClearColor(backgroundColor.getRed(),
		             backgroundColor.getGreen(),
		             backgroundColor.getBlue(),
		              backgroundColor.getAlpha());

		glClear(GL_COLOR_BUFFER_BIT);

		}

		// First reset modelViewMatrix to the identity matrix.
		loadIdentity();

		// Scale it (via matrix multiplication)
		scale(zoom);

		// Rotate (via matrix multiplication)
		rotate(-angle);

		// Translate it (via matrix multiplication)
		translate(-(position));

		if(!isRenderingToTexture){
		
		switch (MainWindow::getInstance().getOrientation()) {
			case WindowOrientation::HORIZONTAL_LEFT:
				rotate(-90.0f);
				translate(Vector2(0, static_cast<float>(MainWindow::getInstance().getRealContextHeight())));
				break;
				
			case WindowOrientation::HORIZONTAL_RIGHT:
				rotate(90);
				translate(Vector2(static_cast<float>(MainWindow::getInstance().getRealContextWidth()), 0));
				break;
				
			default:
				break;
		}
		}

		program->sendUniform(uniforms.modelView, &(modelViewMatrix[0]));

		

	}
	
	/*************************************************************************
	 * Rendering to texture.
	 *************************************************************************/

	void OpenGLDriver::renderToTexture(const TextureInformation *textureInformation, unsigned int viewportWidth, unsigned int viewportHeight, unsigned int contextWidth, unsigned int contextHeight){
		finalizeRender();
		isRenderingToTexture = true;
		if(viewportWidth == 0){
			viewportWidth = textureInformation->imageWidth;
			viewportHeight = textureInformation->imageHeight;
		}
		
		if(contextWidth == 0){
			contextWidth = viewportWidth;
			contextHeight = viewportHeight;
		}
		
		glBindFramebuffer(GL_FRAMEBUFFER, textureFBO);

		
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
		                          GL_TEXTURE_2D, textureInformation->textureId, 0);

		
		glViewport(0, 0, viewportWidth, viewportHeight);
		
		float left, right, bottom, top;
		
		left = 0.0f;
		right = contextWidth;
		bottom = 0.0f;
		top = contextHeight;
		
	
		projectionMatrix[0] = 2.0f / (right - left);
		projectionMatrix[5] = 2.0f / (top- bottom);
		projectionMatrix[10] = -1;
		projectionMatrix[12] = -((right+left)/(right-left));
		projectionMatrix[13] = -((top+bottom)/(top-bottom));
		//		projectionMatrix[14] = 0;
		projectionMatrix[15] = 1;
		
		program->sendUniform(uniforms.projection, &(projectionMatrix[0]));
	}

	void OpenGLDriver::endRenderToTexture(){
		finalizeRender();
		isRenderingToTexture = false;

		glBindFramebuffer(GL_FRAMEBUFFER, originalFramebuffer);


		glViewport(0, 0, static_cast<int>(MainWindow::getInstance().getRealResolutionWidth()), static_cast<int>(MainWindow::getInstance().getRealResolutionHeight()));


		float left, right, bottom, top;

		left = 0.0f;
		right = static_cast<float>(MainWindow::getInstance().getRealContextWidth());
		bottom = static_cast<float>(MainWindow::getInstance().getRealContextHeight());
		top = 0.0f;



		projectionMatrix[0] = 2.0f / (right - left);
		projectionMatrix[5] = 2.0f / (top- bottom);
		projectionMatrix[10] = -1;
		projectionMatrix[12] = -((right+left)/(right-left));
		projectionMatrix[13] = -((top+bottom)/(top-bottom));
		//		projectionMatrix[14] = 0;
		projectionMatrix[15] = 1;

		program->sendUniform(uniforms.projection, &(projectionMatrix[0]));
	}

	/*************************************************************************
	 * Texture management.
	 *************************************************************************/

	void OpenGLDriver::deleteTexture(TextureInformation *textureInfo) {
		glDeleteTextures(1, reinterpret_cast<unsigned int *>(&(textureInfo->textureId)));
		textureInfo->textureId = -1;
	}

	TextureInformation *OpenGLDriver::loadTexture(PixMap *pixMap, TextureInformation *textureInfo) {
		GraphicDriver::loadTexture(pixMap, textureInfo);
		TextureInformation *texInfo;
		if (textureInfo) {
			texInfo = textureInfo;
		}
		else{
			texInfo = new TextureInformation();
		}
		PRLN("Loading texture " << textureInfo->key);
		glGenTextures(1, reinterpret_cast<unsigned int *>(&(texInfo->textureId)));
		glBindTexture(GL_TEXTURE_2D, texInfo->textureId);

		texInfo->imageWidth = pixMap->getWidth();
		texInfo->imageHeight = pixMap->getHeight();

		unsigned int widthPoweredToTwo = MathHelper::nextPowerOf2(pixMap->getWidth());
		unsigned int heightPoweredToTwo = MathHelper::nextPowerOf2(pixMap->getHeight());

		texInfo->poweredWidth = widthPoweredToTwo;
		texInfo->poweredHeight = heightPoweredToTwo;

		GLenum format;
		GLenum type;

		texInfo->colorFormat = pixMap->getColorFormat();

		if (pixMap->getColorFormat() == ColorFormat::RGBA) {
			format = GL_RGBA;
			type = GL_UNSIGNED_BYTE;

		} else if (pixMap->getColorFormat() == ColorFormat::ALPHA){
			format = GL_ALPHA;
			type = GL_UNSIGNED_BYTE;
		}
		else if(pixMap->getColorFormat() == ColorFormat::RGBA4){
			format = GL_RGBA;
			type = GL_UNSIGNED_SHORT_4_4_4_4;
		}else{
			format = GL_RGBA;
			type = GL_UNSIGNED_BYTE;
			Console::error("Loading texture with unrecognized ColorFormat");
		}

		PixMap *poweredTo2Pixmap;
		bool deleteBuffer = false;
		if (pixMap->getBuffer() && widthPoweredToTwo != pixMap->getWidth() && heightPoweredToTwo != pixMap->getHeight()) {
			poweredTo2Pixmap = new PixMap(widthPoweredToTwo, heightPoweredToTwo, 0, pixMap->getColorFormat());
			poweredTo2Pixmap->insertSubPixMap(*pixMap);
			deleteBuffer = true;
		}
		else{
			poweredTo2Pixmap= new PixMap(pixMap->getBuffer(), widthPoweredToTwo, heightPoweredToTwo, pixMap->getColorFormat());
		}


		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


			glTexImage2D(
						 GL_TEXTURE_2D,
						 0,
						 format,
						 widthPoweredToTwo,
						 heightPoweredToTwo,
						 0,
						 format,
						 type,
						 poweredTo2Pixmap->getBuffer());

		if(!deleteBuffer)poweredTo2Pixmap->setBuffer(NULL);
		delete poweredTo2Pixmap;


		return texInfo;
	}

	/*************************************************************************
	 * Initialization and teardown.
	 *************************************************************************/

	void OpenGLDriver::initializeGraphicDriver() {
		GraphicDriver::initializeGraphicDriver();
		#ifdef BB_GLEW
			glewExperimental = GL_TRUE;
			GLenum err;
			err = glewInit();
			if (GLEW_OK != err)
			{
			Console__error("GLEW initialization failed.");
			}

			// Then, we check for some features we need
			if (!glewIsSupported("GL_ARB_framebuffer_object")) {
				Console__print("GL_ARB_framebuffer_object is not supported on your hardware.");
				Console__print("Checking for GL_EXT_framebuffer_object...");
				if (!glewIsSupported("GL_EXT_framebuffer_object")) {
					Console__error("GL_EXT_framebuffer_object is not supported on your hardware.");
				}
				else {
					Console__print("GL_EXT_framebuffer_object is supported.");
					Console__print("Remapping framebuffer extension...");
					glBindFramebuffer = glBindFramebufferEXT;
					glBindRenderbuffer = glBindRenderbufferEXT;
					glCheckFramebufferStatus = glCheckFramebufferStatusEXT;
					glDeleteFramebuffers = glDeleteFramebuffersEXT;
					glDeleteRenderbuffers = glDeleteRenderbuffersEXT;
					glFramebufferRenderbuffer = glFramebufferRenderbufferEXT;
					glFramebufferTexture1D = glFramebufferTexture1DEXT;
					glFramebufferTexture2D = glFramebufferTexture2DEXT;
					glFramebufferTexture3D = glFramebufferTexture3DEXT;
					glGenFramebuffers = glGenFramebuffersEXT;
					glGenRenderbuffers = glGenRenderbuffersEXT;
					glGenerateMipmap = glGenerateMipmapEXT;
					glGetFramebufferAttachmentParameteriv = glGetFramebufferAttachmentParameterivEXT;
					glGetRenderbufferParameteriv = glGetRenderbufferParameterivEXT;
					glIsFramebuffer = glIsFramebufferEXT;
					glIsRenderbuffer = glIsRenderbufferEXT;
					glRenderbufferStorage = glRenderbufferStorageEXT;
					Console__print("All done!");
				}
			}
		#endif // BB_GLEW

		if(!shaderCompiled){
			shaderCompiled = true;

			std::string vertexShader =
			"uniform mat4 projection;\
			uniform mat4 modelView;\
			\
			attribute vec2 position;\
			attribute vec2 texcoordIN;\
			attribute vec4 colorOffsetIN;\
			attribute vec4 colorIN;\
			varying vec2 texcoord;\
			varying vec4 colorOffset;\
			varying vec4 color;\
			void main(void) {\
			mat4 modelViewProjection = (projection * modelView);\
			texcoord = texcoordIN;\
			colorOffset = colorOffsetIN;\
			color = colorIN;\
			gl_Position =   modelViewProjection * vec4(position, 0.0, 1.0);\
			}";

			std::string vertexShaderNoColor =
			"uniform mat4 projection;\
			uniform mat4 modelView;\
			\
			attribute vec2 position;\
			attribute vec2 texcoordIN;\
			varying vec2 texcoord;\
			void main(void) {\
			mat4 modelViewProjection = (projection * modelView);\
			texcoord = texcoordIN;\
			gl_Position =   modelViewProjection * vec4(position, 0.0, 1.0);\
			}";

			std::string fragmentShaderAlpha =
			"uniform bool  alphaFormat;\
			uniform sampler2D  tex;\
			varying vec2 texcoord;\
			varying vec4 colorOffset;\
			varying vec4 color;\
			void main(void) {\
			vec4 texColor = texture2D(tex, texcoord);\
			texColor = vec4(vec3(1.0), texColor.a); \
			gl_FragColor = (texColor * color) +colorOffset;\
			}";

			std::string fragmentShaderAlphaNoColor =
			"uniform bool  alphaFormat;\
			uniform sampler2D  tex;\
			varying vec2 texcoord;\
			void main(void) {\
			vec4 texColor = texture2D(tex, texcoord);\
			texColor = vec4(vec3(1.0), texColor.a); \
			gl_FragColor = (texColor);\
			}";

			std::string fragmentShaderNoColor =
			"uniform bool  alphaFormat;\
			uniform sampler2D  tex;\
			varying vec2 texcoord;\
			void main(void) {\
			vec4 texColor = texture2D(tex, texcoord);\
			gl_FragColor = texColor;\
			}";

			std::string fragmentShader =
			"uniform bool  alphaFormat;\
			uniform sampler2D  tex;\
			varying vec2 texcoord;\
			varying vec4 colorOffset;\
			varying vec4 color;\
			void main(void) {\
			vec4 texColor = texture2D(tex, texcoord);\
			gl_FragColor = (texColor * color) +colorOffset;\
			}";

			std::string fragmentShaderWithoutTexture =
			"uniform bool  alphaFormat;\
			varying vec4 colorOffset;\
			varying vec4 color;\
			void main(void) {\
			gl_FragColor = color + colorOffset;\
			}";

#ifdef BB_OPENGLES
			// For OpenGL ES, sets the float precision by prepending to all programs.
			std::string GLESPrecisionVertex = "precision highp float;\n";
			std::string GLESPrecisionFragment = "precision highp float;\n";

			vertexShaderNoColor.insert(0, GLESPrecisionVertex);
			vertexShader       .insert(0, GLESPrecisionVertex);

			fragmentShaderAlpha          .insert(0, GLESPrecisionFragment);
			fragmentShaderNoColor        .insert(0, GLESPrecisionFragment);
			fragmentShader               .insert(0, GLESPrecisionFragment);
			fragmentShaderWithoutTexture .insert(0, GLESPrecisionFragment);
			fragmentShaderAlphaNoColor   .insert(0, GLESPrecisionFragment);
#endif

			alphaProgram             = internalMakeProgram(vertexShader,       fragmentShaderAlpha);
			rgbProgram               = internalMakeProgram(vertexShader,       fragmentShader);
			rgbWithoutTextureProgram = internalMakeProgram(vertexShader,       fragmentShaderWithoutTexture);
			rgbNoTransformProgram    = internalMakeProgram(vertexShaderNoColor,fragmentShaderNoColor, false);
			alphaNoTransformProgram  = internalMakeProgram(vertexShaderNoColor,fragmentShaderAlphaNoColor, false);

			// Default/first program.
			program = rgbProgram;
			program->use();

			uniforms.tex = program->getUniformLocation("tex");
			uniforms.projection = program->getUniformLocation("projection");
			uniforms.modelView= program->getUniformLocation("modelView");

			program->sendUniform(uniforms.tex, 0);
			program->sendUniform(uniforms.modelView, &(modelViewMatrix[0]));
		}

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnableVertexAttribArray(attributes.colorOffset);
		glEnableVertexAttribArray(attributes.color);
		glEnableVertexAttribArray(attributes.vertices);
		glEnableVertexAttribArray(attributes.texCoord);

		GLint tempBuffer;
		glGetIntegerv(GL_FRAMEBUFFER_BINDING, &tempBuffer);
		originalFramebuffer = static_cast<GLuint>(tempBuffer);

		if(textureFBOInitialized){
			glDeleteFramebuffers(1, &textureFBO);
		}

		glGenFramebuffers(1, &textureFBO);
		textureFBOInitialized = true;

		resetProjection();

#if defined(BB_MAC_PLATFORM) && defined(BB_SDL)
		int swapInterval = 1;
		CGLSetParameter(CGLGetCurrentContext(), kCGLCPSwapInterval, &swapInterval);
#endif
	}

	inline GLSLProgram * OpenGLDriver::internalMakeProgram(std::string vertexShader, std::string fragmentShader, bool hasColorTransform) {
		GLSLProgram * program = new GLSLProgram(vertexShader, fragmentShader);

		program->setAttributeLocation("position", attributes.vertices);
		program->setAttributeLocation("texcoordIN", attributes.texCoord);
		if (hasColorTransform) {
			program->setAttributeLocation("colorIN", attributes.color);
			program->setAttributeLocation("colorOffsetIN", attributes.colorOffset);
		}

		program->link();

		return program;
	}

	void OpenGLDriver::tearGraphicDriver(){
		ResourceManager::unloadAllTexture();

		lastGPUState = GPUState();


		shaderCompiled = false;

		if(alphaProgram) delete alphaProgram;
		if(rgbProgram) delete rgbProgram;
		if(rgbNoTransformProgram) delete rgbNoTransformProgram;
		if(alphaNoTransformProgram) delete alphaNoTransformProgram;
		alphaProgram = NULL;
		rgbProgram = NULL;
		rgbNoTransformProgram = NULL;
		alphaNoTransformProgram = NULL;
		program = NULL;

	}

	void OpenGLDriver::finalizeRender() {
		if (this->lastTexture) {
			this->batch.render(this, this->lastTexture, true);
			this->lastTexture = NULL;
		}
	}

	OpenGLDriver::OpenGLDriver() : GraphicDriver(),
		batch(), lastShapeBlend(true), lastShapeColorTransform(false),
		program(NULL), shaderCompiled(false),
		lastGPUState(), currentGPUState(), lastTexture(NULL),
		projectionMatrix(16,0), modelViewMatrix(16,0), tempTransformMatrix(16,0),
		textureFBOInitialized(false), isRenderingToTexture(false) {
		noTexture = new TextureInformation();
		noTexture->textureId = 0;
		noTexture->path = "NO TEXTURE";
		noTexture->key  = "NO TEXTURE";
	}

	OpenGLDriver::~OpenGLDriver() {
		delete noTexture;
	}

	/*************************************************************************
	 * Matrices, projection and transformation.
	 *************************************************************************/

	void OpenGLDriver::resetProjection(){
		glViewport(0, 0, static_cast<int>(MainWindow::getInstance().getRealResolutionWidth()), static_cast<int>(MainWindow::getInstance().getRealResolutionHeight()));


		float left, right, bottom, top;

		left = 0.0f;
		right = static_cast<float>(MainWindow::getInstance().getRealContextWidth());
		bottom = static_cast<float>(MainWindow::getInstance().getRealContextHeight());
		top = 0.0f;


		projectionMatrix[0] = 2.0f / (right - left);
		projectionMatrix[5] = 2.0f / (top- bottom);
		projectionMatrix[10] = -1;
		projectionMatrix[12] = -((right+left)/(right-left));
		projectionMatrix[13] = -((top+bottom)/(top-bottom));
		//		projectionMatrix[14] = 0;
		projectionMatrix[15] = 1;

		program->sendUniform(uniforms.projection, &(projectionMatrix[0]));
	}


	//inspired by http://www.flashbang.se/archives/148
	/* https://open.gl/transformations → Translation
	 *  x = translation.x
	 *  y = translation.y
	 * ┌         ┐
	 * │ 1 0 0 0 │
	 * │ 0 1 0 0 │
	 * │ 0 0 1 0 │
	 * │ x y 0 1 │
	 * └         ┘
	 * OpenGL ES cannot transpose a matrix, this means that we need to supply the
	 * translation matrix as OpenGL will use it.
	 * > The translation components occupy the 13th, 14th, and 15th elements of the 16-element matrix
	 */
	void OpenGLDriver::translate(const Vector2 &translation) {


		tempTransformMatrix[0]  = 1;
		tempTransformMatrix[4]  = 0;
		tempTransformMatrix[8]  = 0;
		tempTransformMatrix[12] = translation.x;

		tempTransformMatrix[1]  = 0;
		tempTransformMatrix[5]  = 1;
		tempTransformMatrix[9]  = 0;
		tempTransformMatrix[13] = translation.y;

		tempTransformMatrix[2]  = 0;
		tempTransformMatrix[6]  = 0;
		tempTransformMatrix[10] = 1;
		tempTransformMatrix[14] = 0;

		tempTransformMatrix[3]  = 0;//translation.x;
		tempTransformMatrix[7]  = 0;//translation.y;
		tempTransformMatrix[11] = 0;
		tempTransformMatrix[15] = 1;

		multMatrix(&(modelViewMatrix[0]),&(tempTransformMatrix[0]));
	}

	//inspired by http://www.flashbang.se/archives/148
	/* https://open.gl/transformations → Scaling
	 *  x = scale.x
	 *  y = scale.y
	 * ┌         ┐
	 * │ x 0 0 0 │
	 * │ 0 y 0 0 │
	 * │ 0 0 1 0 │
	 * │ 0 0 0 1 │
	 * └         ┘
	 */
	void OpenGLDriver::scale(const Vector2 &scale){

		tempTransformMatrix[0]  = scale.x;
		tempTransformMatrix[4]  = 0;
		tempTransformMatrix[8]  = 0;
		tempTransformMatrix[12] = 0;

		tempTransformMatrix[1]  = 0;
		tempTransformMatrix[5]  = scale.y;
		tempTransformMatrix[9]  = 0;
		tempTransformMatrix[13] = 0;

		tempTransformMatrix[2]  = 0;
		tempTransformMatrix[6]  = 0;
		tempTransformMatrix[10] = 1;
		tempTransformMatrix[14] = 0;

		tempTransformMatrix[3]  = 0;
		tempTransformMatrix[7]  = 0;
		tempTransformMatrix[11] = 0;
		tempTransformMatrix[15] = 1;

		multMatrix(&(modelViewMatrix[0]),&(tempTransformMatrix[0]));
	}

	//inspired by http://www.flashbang.se/archives/148
	/* https://open.gl/transformations → Rotation
	 * ┌         ┐
	 * │ _ _ _ 0 │
	 * │ _ _ _ 0 │
	 * │ _ _ _ 0 │
	 * │ 0 0 0 1 │
	 * └         ┘
	 * For the _, see the previously linked resources.
	 */
	void OpenGLDriver::rotate(float a){
		float angle    = a * MathHelper::PI_OVER_180 ;
		float sinAngle = MathHelper::sin(angle);
		float cosAngle = MathHelper::cos(angle);

		float x = 0;
		float y = 0;
		float z = 1;

		// Matrix multiplications for the different axes are pre-baked.
		tempTransformMatrix[0]  = 1+(1-cosAngle)*(x*x-1);
		tempTransformMatrix[4]  = -z*sinAngle+(1-cosAngle)*x*y;
		tempTransformMatrix[8]  = y*sinAngle+(1-cosAngle)*x*z;
		tempTransformMatrix[12] = 0;

		tempTransformMatrix[1]  = z*sinAngle+(1-cosAngle)*x*y;
		tempTransformMatrix[5]  = 1+(1-cosAngle)*(y*y-1);
		tempTransformMatrix[9]  = -x*sinAngle+(1-cosAngle)*y*z;
		tempTransformMatrix[13] = 0;

		tempTransformMatrix[2]  = -y*sinAngle+(1-cosAngle)*x*z;
		tempTransformMatrix[6]  = x*sinAngle+(1-cosAngle)*y*z;
		tempTransformMatrix[10] = 1+(1-cosAngle)*(z*z-1);
		tempTransformMatrix[14] = 0;

		tempTransformMatrix[3]  = 0;
		tempTransformMatrix[7]  = 0;
		tempTransformMatrix[11] = 0;
		tempTransformMatrix[15] = 1;

		multMatrix(&(modelViewMatrix[0]),&(tempTransformMatrix[0]));
	}


	//inspired by http://www.flashbang.se/archives/148
	/*
	 *                         ┌         ┐┌         ┐
	 *                         │ a b c d ││ A B C D │
	 *                         │ e f g h ││ E F G H │
	 *                         │ i j k l ││ I J K L │ =
	 *                         │ m n o p ││ M N O P │
	 *                         └         ┘└         ┘
	 * ┌                                                                                ┐
	 * │ aA + bE + cI + dM   aB + bF + cJ + dN   aC + bG + cK + dO   aD + bH + cL + dP │
	 * │ eA + fE + gI + hM   eB + fF + gJ + hN   eC + fG + gK + hO   eD + fH + gL + hP │
	 * │ iA + jE + kI + lM   iB + jF + kJ + lN   iC + jG + kK + lO   iD + jH + kL + lP │
	 * │ mA + nE + oI + pM   mB + nF + oJ + pN   mC + nG + oK + pO   mD + nH + oL + pP │
	 * └                                                                                ┘

	*/
	void OpenGLDriver::multMatrix(float *MatrixB,float MatrixA[16])
	{
		float NewMatrix[16];
		int i;
		for(i = 0; i < 4; i++){ //Cycle through each vector of first matrix.
			int i1 = i;
			int i2 = i + 4;
			int i3 = i + 8;
			int i4 = i + 12;
			NewMatrix[i1] = MatrixA[i1] * MatrixB[0] + MatrixA[i2] * MatrixB[1] + MatrixA[i3] * MatrixB[2] + MatrixA[i4] * MatrixB[3];
			NewMatrix[i2] = MatrixA[i1] * MatrixB[4] + MatrixA[i2] * MatrixB[5] + MatrixA[i3] * MatrixB[6] + MatrixA[i4] * MatrixB[7];
			NewMatrix[i3] = MatrixA[i1] * MatrixB[8] + MatrixA[i2] * MatrixB[9] + MatrixA[i3] * MatrixB[10] + MatrixA[i4] * MatrixB[11];
			NewMatrix[i4] = MatrixA[i1] * MatrixB[12] + MatrixA[i2] * MatrixB[13] + MatrixA[i3] * MatrixB[14] + MatrixA[i4] * MatrixB[15];
		}
		/*this should combine the matrixes*/

		memcpy(MatrixB,NewMatrix,64);
	}


	//inspired by http://www.flashbang.se/archives/148
	/* ┌         ┐
	 * │ 1 0 0 0 │
	 * │ 0 1 0 0 │
	 * │ 0 0 1 0 │
	 * │ 0 0 0 1 │
	 * └         ┘
	 */
	void OpenGLDriver::loadIdentity() {
		modelViewMatrix[0] = 1;
		modelViewMatrix[4] = 0;
		modelViewMatrix[8] = 0;
		modelViewMatrix[12] = 0;

		modelViewMatrix[1] = 0;
		modelViewMatrix[5] = 1;
		modelViewMatrix[9] = 0;
		modelViewMatrix[13] = 0;

		modelViewMatrix[2] = 0;
		modelViewMatrix[6] = 0;
		modelViewMatrix[10] = 1;
		modelViewMatrix[14] = 0;

		modelViewMatrix[3] = 0;
		modelViewMatrix[7] = 0;
		modelViewMatrix[11] = 0;
		modelViewMatrix[15] = 1;
	}

	void OpenGLDriver::pushMatrix() {}

	void OpenGLDriver::popMatrix() {}
}
