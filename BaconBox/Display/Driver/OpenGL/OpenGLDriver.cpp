#include "BaconBox/Display/Driver/OpenGL/OpenGLDriver.h"

#include <stdint.h>

#include "BaconBox/PlatformFlagger.h"
#include "BaconBox/Display/TextureInformation.h"
#include "BaconBox/Helper/MathHelper.h"
#include "BaconBox/Display/Window/MainWindow.h"
#include "BaconBox/VertexArray.h"
#include "BaconBox/Display/Color.h"
#include "BaconBox/Console.h"

#define GET_PTR(vertices) reinterpret_cast<const GLfloat *>(&(*vertices.getBegin()))
#define GET_TEX_PTR(textureCoordinates) reinterpret_cast<const GLfloat *>(&(*textureCoordinates.begin()))
#define GET_PTR_BATCH(vertices, adjustment) reinterpret_cast<const GLfloat *>(&(*(vertices.getBegin() + adjustment)))
#define GET_TEX_PTR_BATCH(textureCoordinates, adjustment) reinterpret_cast<const GLfloat *>(&(*(textureCoordinates.begin() + adjustment)))


namespace BaconBox {


	void OpenGLDriver::drawShapeWithTextureColorColorOffset(const VertexArray &vertices,
                  const TextureInformation *textureInformation,
                  const TextureCoordinates &textureCoordinates,
                  const Color &color,
                  const Color &colorOffset, bool blend){
		if (this->lastTexture){
			if(textureInformation != this->lastTexture || blend != lastShapeBlend) {
				this->batch.render(this, this->lastTexture, lastShapeBlend);
				this->batch.prepareRender();
			}
		}
		else{
			this->batch.prepareRender();
		}
		
						this->batch.addItem(vertices, color, colorOffset, textureCoordinates);
						this->lastTexture = textureInformation;
						lastShapeBlend = blend;

	}


	void OpenGLDriver::drawBatchWithTextureColorColorOffset(const VertexArray &vertices,
		                                  const TextureInformation *textureInformation,
		                                  const TextureCoordinates &textureCoordinates,
		                                  const IndiceArray &indices,
		                                  const ColorArray &colors,
		                                  const ColorArray &colorOffsets, bool blend){
		
		


			currentGPUState.textureID = textureInformation->textureId;
			currentGPUState.textureCoordinates = GET_TEX_PTR_BATCH(textureCoordinates, 0);
			currentGPUState.vertices = GET_PTR_BATCH(vertices, 0);
			currentGPUState.colors = GET_TEX_PTR_BATCH(colors, 0);
			currentGPUState.colorOffsets = GET_TEX_PTR_BATCH(colorOffsets, 0);
			currentGPUState.format = textureInformation->colorFormat;
			currentGPUState.blend = blend;
			
			if(! (currentGPUState.format == lastGPUState.format) ){
				lastGPUState.format = currentGPUState.format;
				if(textureInformation->colorFormat == ColorFormat::ALPHA){
					program->sendUniform(uniforms.alphaFormat,GL_TRUE);
//					program = alphaProgram;
//					program->use();
					
				}
				else{
					program->sendUniform(uniforms.alphaFormat,GL_FALSE);
//					program = rgbProgram;
//					program->use();
				}
			}
			if(lastGPUState.blend != currentGPUState.blend){
				if(blend){
					glEnable(GL_BLEND);

				}
				else{
					glDisable(GL_BLEND);
				}
				lastGPUState.blend = currentGPUState.blend;
			}
			
			if(! (currentGPUState.textureID == lastGPUState.textureID) ){
				lastGPUState.textureID = currentGPUState.textureID;
				glBindTexture(GL_TEXTURE_2D, textureInformation->textureId);
			}
			if(! (currentGPUState.textureCoordinates == lastGPUState.textureCoordinates) ){
				lastGPUState.textureCoordinates = currentGPUState.textureCoordinates;
				glVertexAttribPointer(attributes.texCoord, 2, GL_FLOAT, GL_FALSE, 0, currentGPUState.textureCoordinates);
			}
			if(! (currentGPUState.vertices == lastGPUState.vertices) ){
				lastGPUState.vertices = currentGPUState.vertices;
				glVertexAttribPointer(attributes.vertices, 2, GL_FLOAT, GL_FALSE, 0, currentGPUState.vertices);
			}
			if(! (currentGPUState.colors == lastGPUState.colors) ){
				lastGPUState.colors = currentGPUState.colors;
				glVertexAttribPointer(attributes.color, 4, GL_FLOAT, GL_FALSE, 0,  currentGPUState.colors);
			}
			if(! (currentGPUState.colorOffsets == lastGPUState.colorOffsets) ){
				lastGPUState.colorOffsets = currentGPUState.colorOffsets;
				glVertexAttribPointer(attributes.colorOffset, 4, GL_FLOAT, GL_FALSE, 0, currentGPUState.colorOffsets);
			}

			glDrawElements(GL_TRIANGLE_STRIP, indices.size(), GL_UNSIGNED_SHORT, &(indices[0]));
  }


	void OpenGLDriver::prepareScene(const Vector2 &position, float angle,
	                                const Vector2 &zoom,
	                                const Color &backgroundColor, bool clearScreen) {
		if(clearScreen){
		glClearColor(backgroundColor.getRed(),
		             backgroundColor.getGreen(),
		             backgroundColor.getBlue(),
		             1.0f);

		glClear(GL_COLOR_BUFFER_BIT);
		}

		loadIdentity();

		switch (MainWindow::getInstance().getOrientation().underlying()) {
		case WindowOrientation::HORIZONTAL_LEFT:
			rotate(-90.0f);
			translate(Vector2(static_cast<float>(MainWindow::getInstance().getContextWidth()), 0.0f));
			break;

		case WindowOrientation::HORIZONTAL_RIGHT:
			rotate(90.0f);
			translate(Vector2(0.0f, -static_cast<float>(MainWindow::getInstance().getContextHeight())));
			break;

		default:
			break;
		}

		scale(zoom);
		rotate(angle);
		translate(-(position));
		program->sendUniform(uniforms.modelView, &(modelViewMatrix[0]));



	}

	void OpenGLDriver::initializeGraphicDriver() {
		GraphicDriver::initializeGraphicDriver();

		#ifdef BB_GLEW
		 GLenum err;
           err = glewInit();
            if (GLEW_OK != err)
            {
                Console__error("GLEW INIT FAILED!");
            }

		#endif // BB_GLEW
		std::string vertexShader;
#ifdef BB_IPHONE_PLATFORM
		vertexShader += "precision mediump float;\n";
#endif
		vertexShader += "uniform mat4 projection;\
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
		
		std::string fragmentShader;
		
#ifdef BB_IPHONE_PLATFORM
		fragmentShader += "precision lowp float;\n";
#endif
		fragmentShader += "uniform bool  alphaFormat;\
		uniform sampler2D  tex;\
		varying vec2 texcoord;\
		varying vec4 colorOffset;\
		varying vec4 color;\
		void main(void) {\
		vec4 texColor = texture2D(tex, texcoord);\
		if(alphaFormat){\
		texColor = vec4(vec3(1.0), texColor.a); \
		} \
		gl_FragColor = (texColor * color) +colorOffset;\
		}";
		
		program = new GLSLProgram(vertexShader,fragmentShader);

    		program->use();
		
			uniforms.tex = program->getUniformLocation("tex");
			uniforms.alphaFormat = program->getUniformLocation("alphaFormat");
			uniforms.projection = program->getUniformLocation("projection");
			uniforms.modelView= program->getUniformLocation("modelView");
		
    		program->sendUniform(uniforms.tex, 0);
            program->sendUniform(uniforms.alphaFormat, GL_FALSE);
		
		
			attributes.vertices = program->getAttributeLocation("position");
			attributes.texCoord = program->getAttributeLocation("texcoordIN");
            attributes.colorOffset = program->getAttributeLocation("colorOffsetIN");
			attributes.color = program->getAttributeLocation("colorIN");
		
		
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
        glEnableVertexAttribArray(attributes.colorOffset);
		glEnableVertexAttribArray(attributes.color);
		glEnableVertexAttribArray(attributes.vertices);
		glEnableVertexAttribArray(attributes.texCoord);


		if (MainWindow::getInstance().getOrientation() == WindowOrientation::NORMAL ||
		    MainWindow::getInstance().getOrientation() == WindowOrientation::UPSIDE_DOWN) {
			glViewport(0, 0, static_cast<int>(MainWindow::getInstance().getResolutionWidth()), static_cast<int>(MainWindow::getInstance().getResolutionHeight()));

		} else {
			glViewport(0, 0, static_cast<int>(MainWindow::getInstance().getResolutionHeight()), static_cast<int>(MainWindow::getInstance().getResolutionWidth()));
		}


		float left, right, bottom, top;

		if (MainWindow::getInstance().getOrientation() == WindowOrientation::NORMAL) {
			left = 0.0f;
			right = static_cast<float>(MainWindow::getInstance().getContextWidth());
			bottom = static_cast<float>(MainWindow::getInstance().getContextHeight());
			top = 0.0f;

		} else if (MainWindow::getInstance().getOrientation() == WindowOrientation::UPSIDE_DOWN) {
			left = 0.0f;
			right = static_cast<float>(MainWindow::getInstance().getContextWidth());
			bottom = 0.0f;
			top = static_cast<float>(MainWindow::getInstance().getContextHeight());

		} else if (MainWindow::getInstance().getOrientation() == WindowOrientation::HORIZONTAL_LEFT) {
			left = static_cast<float>(MainWindow::getInstance().getContextHeight());
			right = 0.0f;
			bottom = 0.0f;
			top = static_cast<float>(MainWindow::getInstance().getContextWidth());

		} else { //if (MainWindow::getInstance().getOrientation() == WindowOrientation::HORIZONTAL_RIGHT)
			left = static_cast<float>(MainWindow::getInstance().getContextHeight());
			right = 0.0f;
			bottom = 0.0f;
			top = static_cast<float>(MainWindow::getInstance().getContextWidth());
		}
		
		


		std::vector<float> projectionMatrix(16,0);
		projectionMatrix[0] = 2.0f / (right - left);
		projectionMatrix[5] = 2.0f / (top- bottom);
		projectionMatrix[10] = -1;
		projectionMatrix[12] = -((right+left)/(right-left));
		projectionMatrix[13] = -((top+bottom)/(top-bottom));
//		projectionMatrix[14] = 0;
		projectionMatrix[15] = 1;
		
		program->sendUniform(uniforms.projection, &(projectionMatrix[0]));
#if defined(BB_MAC_PLATFORM) && defined(BB_SDL)
		int swapInterval = 1;
		CGLSetParameter(CGLGetCurrentContext(), kCGLCPSwapInterval, &swapInterval);
#endif
		

	}

	void OpenGLDriver::pushMatrix() {
	}

	
	//inspired by http://www.flashbang.se/archives/148
	void OpenGLDriver::translate(const Vector2 &translation) {

		
		tempTransformMatrix[0] = 1;
		tempTransformMatrix[4] = 0;
		tempTransformMatrix[8] = 0;
		tempTransformMatrix[12] = 0;
		
		tempTransformMatrix[1] = 0;
		tempTransformMatrix[5] = 1;
		tempTransformMatrix[9] = 0;
		tempTransformMatrix[13] = 0;
		
		tempTransformMatrix[2] = 0;
		tempTransformMatrix[6] = 0;
		tempTransformMatrix[10] = 1;
		tempTransformMatrix[14] = 0;
		
		tempTransformMatrix[3] = translation.x;
		tempTransformMatrix[7] = translation.y;
		tempTransformMatrix[12] = 0;
		tempTransformMatrix[15] = 1;
		
		multMatrix(&(modelViewMatrix[0]),&(tempTransformMatrix[0]));
	}
	
	//inspired by http://www.flashbang.se/archives/148
	void OpenGLDriver::scale(const Vector2 &scale){
		
		tempTransformMatrix[0] = scale.x;
		tempTransformMatrix[4] = 0;
		tempTransformMatrix[8] = 0;
		tempTransformMatrix[12] = 0;
		
		tempTransformMatrix[1] = 0;
		tempTransformMatrix[5] = scale.y;
		tempTransformMatrix[9] = 0;
		tempTransformMatrix[13] = 0;
		
		tempTransformMatrix[2] = 0;
		tempTransformMatrix[6] = 0;
		tempTransformMatrix[10] = 1;
		tempTransformMatrix[14] = 0;
		
		tempTransformMatrix[3] = 0;
		tempTransformMatrix[7] = 0;
		tempTransformMatrix[11] = 0;
		tempTransformMatrix[15] = 1;
		
		multMatrix(&(modelViewMatrix[0]),&(tempTransformMatrix[0]));
	}
	
	//inspired by http://www.flashbang.se/archives/148
	void OpenGLDriver::rotate(float a){
		float angle= a * MathHelper::PI_OVER_180 ;
		
		tempTransformMatrix[0] = 1;
		tempTransformMatrix[4] = -MathHelper::sin(angle);
		tempTransformMatrix[8] = 0;
		tempTransformMatrix[12] = 0;
		
		tempTransformMatrix[1] = MathHelper::sin(angle);
		tempTransformMatrix[5] = 1-(1-MathHelper::cos(angle));
		tempTransformMatrix[9] = 0;
		tempTransformMatrix[13] = 0;
		
		tempTransformMatrix[2] = 0;
		tempTransformMatrix[6] = 0;
		tempTransformMatrix[10] = 1;
		tempTransformMatrix[14] = 0;
		
		tempTransformMatrix[3] = 0;
		tempTransformMatrix[7] = 0;
		tempTransformMatrix[12] = 0;
		tempTransformMatrix[15] = 1;
		
		multMatrix(&(modelViewMatrix[0]),&(tempTransformMatrix[0]));
	}

	//inspired by http://www.flashbang.se/archives/148
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

	void OpenGLDriver::popMatrix() {
	}


	void OpenGLDriver::deleteTexture(TextureInformation *textureInfo) {
		glDeleteTextures(1, reinterpret_cast<unsigned int *>(&(textureInfo->textureId)));
		textureInfo->textureId = -1;
	}

	TextureInformation *OpenGLDriver::loadTexture(PixMap *pixMap) {
		GraphicDriver::loadTexture(pixMap);

		TextureInformation *texInfo = new TextureInformation();
		glGenTextures(1, reinterpret_cast<unsigned int *>(&(texInfo->textureId)));
		glBindTexture(GL_TEXTURE_2D, texInfo->textureId);

		texInfo->imageWidth = pixMap->getWidth();
		texInfo->imageHeight = pixMap->getHeight();

		int widthPoweredToTwo = MathHelper::nextPowerOf2(pixMap->getWidth());
		int heightPoweredToTwo = MathHelper::nextPowerOf2(pixMap->getHeight());

		texInfo->poweredWidth = widthPoweredToTwo;
		texInfo->poweredHeight = heightPoweredToTwo;

		GLint format;
		texInfo->colorFormat = pixMap->getColorFormat();

		if (pixMap->getColorFormat() == ColorFormat::RGBA) {
			format = GL_RGBA;

		} else { // if (pixMap->getColorFormat() == ColorFormat::ALPHA)
			format = GL_ALPHA;
		}

		if (widthPoweredToTwo == pixMap->getWidth() && heightPoweredToTwo == pixMap->getHeight()) {
			glTexImage2D(
						 GL_TEXTURE_2D,
						 0,
						 format,
						 widthPoweredToTwo,
						 heightPoweredToTwo,
						 0,
						 format,
						 GL_UNSIGNED_BYTE,
						 pixMap->getBuffer());
		} else {
			PixMap poweredTo2Pixmap(widthPoweredToTwo, heightPoweredToTwo, pixMap->getColorFormat());
			poweredTo2Pixmap.insertSubPixMap(*pixMap);

			glTexImage2D(
						 GL_TEXTURE_2D,
						 0,
						 format,
						 widthPoweredToTwo,
						 heightPoweredToTwo,
						 0,
						 format,
						 GL_UNSIGNED_BYTE,
						 poweredTo2Pixmap.getBuffer());
		}

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		return texInfo;
	}

	void OpenGLDriver::finalizeRender() {
		if (this->lastTexture) {
			this->batch.render(this, this->lastTexture, true);
			this->lastTexture = NULL;
		}
	}



	OpenGLDriver::OpenGLDriver() : GraphicDriver(), batch(), lastShapeBlend(true),lastTexture(NULL), modelViewMatrix(16,0), tempTransformMatrix(16,0), lastGPUState(), currentGPUState() {
	}

	OpenGLDriver::~OpenGLDriver() {

	}
}
