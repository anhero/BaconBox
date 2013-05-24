#include "BaconBox/Display/Driver/OpenGL/OpenGLDriver.h"

#include <stdint.h>

#include "BaconBox/PlatformFlagger.h"
#include "BaconBox/Display/TextureInformation.h"
#include "BaconBox/Helper/MathHelper.h"
#include "BaconBox/Display/Window/MainWindow.h"
#include "BaconBox/VertexArray.h"
#include "BaconBox/Display/Color.h"
#include "BaconBox/Display/PixMap.h"
#include "BaconBox/Console.h"

#define GET_PTR(vertices) reinterpret_cast<const GLfloat *>(&(*vertices.getBegin()))
#define GET_TEX_PTR(textureCoordinates) reinterpret_cast<const GLfloat *>(&(*textureCoordinates.begin()))
#define GET_PTR_BATCH(vertices, adjustment) reinterpret_cast<const GLfloat *>(&(*(vertices.getBegin() + adjustment)))
#define GET_TEX_PTR_BATCH(textureCoordinates, adjustment) reinterpret_cast<const GLfloat *>(&(*(textureCoordinates.begin() + adjustment)))


namespace BaconBox {
	void OpenGLDriver::drawShapeWithTextureAndColor(const VertexArray &vertices,
	                                                const TextureInformation *textureInformation,
	                                                const TextureCoordinates &textureCoordinates,
	                                                const Color &color) {
        ColorTransformArray white = ColorTransformArray(4, 1);
        ColorTransformArray black = ColorTransformArray(4, 0);
		if (textureInformation != this->lastTexture) {
//			if (this->batch.isSingle()) {
//				this->internalDrawShapeWithTextureAndColorTransform(this->batch.getVertices(), this->lastTexture, this->batch.getTextureCoordinates(), this->batch.getColor(), white, black);
//			} else
			if (this->lastTexture) {
				this->batch.render(this, this->lastTexture);
			}

			this->batch.prepareRender();
			this->lastTexture = textureInformation;
		}

		this->batch.addItem(vertices, color, white, black, textureCoordinates);
	}


	void OpenGLDriver::drawShapeWithTextureAndColorTransform(const VertexArray &vertices,
                  const TextureInformation *textureInformation,
                  const TextureCoordinates &textureCoordinates,
                  const Color &color,
                  const ColorTransformArray &colorMultiplier,
                  const ColorTransformArray &colorOffset){
                    if (textureInformation != this->lastTexture) {
//                        if (this->batch.isSingle()) {
//                            this->internalDrawShapeWithTextureAndColorTransform(this->batch.getVertices(), this->lastTexture, this->batch.getTextureCoordinates(), this->batch.getColor(), colorMultiplier, colorOffset);
//                        } else
							if (this->lastTexture) {
                            this->batch.render(this, this->lastTexture);
                        }

                        this->batch.prepareRender();
                        this->lastTexture = textureInformation;
                    }

                    this->batch.addItem(vertices, color, colorMultiplier, colorOffset, textureCoordinates);

                  }

//	void OpenGLDriver::drawShapeWithTexture(const VertexArray &vertices,
//	                                        const TextureInformation *textureInformation,
//	                                        const TextureCoordinates &textureCoordinates) {
//		// We make sure the texture information is valid.
//		if (textureInformation) {
//			glBindTexture(GL_TEXTURE_2D, textureInformation->textureId);
//
//			glEnable(GL_TEXTURE_2D);
//			glEnable(GL_BLEND);
//#ifdef BB_OPENGLES
//			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//#else
//			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//#endif
//
//			glVertexPointer(2, GL_FLOAT, 0, GET_PTR(vertices));
//			glEnableClientState(GL_VERTEX_ARRAY);
//
//			glTexCoordPointer(2, GL_FLOAT, 0, GET_TEX_PTR(textureCoordinates));
//			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
//
//            if(textureInformation->colorFormat == ColorFormat::ALPHA){
//                program->sendUniform("alphaFormat",GL_TRUE);
//
//			}
//			else{
//                program->sendUniform("alphaFormat",GL_FALSE);
//			}
//			glDrawArrays(GL_TRIANGLE_STRIP, 0, static_cast<GLsizei>(vertices.getNbVertices()));
//
//			glDisableClientState(GL_VERTEX_ARRAY);
//			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
//			glDisable(GL_BLEND);
//			glDisable(GL_TEXTURE_2D);
//
//		}
//	}

//	void OpenGLDriver::drawShapeWithColor(const VertexArray &vertices,
//	                                      const Color &color) {
//		if (color.getAlpha() > 0u) {
//			glColor4ub(color.getRed(), color.getGreen(), color.getBlue(),
//			           color.getAlpha());
//
//			glVertexPointer(2, GL_FLOAT, 0, GET_PTR(vertices));
//			glEnable(GL_BLEND);
//
//#ifdef BB_OPENGLES
//			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//#else
//			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//#endif
//			glEnableClientState(GL_VERTEX_ARRAY);
//
//			glDrawArrays(GL_TRIANGLE_STRIP, 0, static_cast<GLsizei>(vertices.getNbVertices()));
//
//			glDisableClientState(GL_VERTEX_ARRAY);
//			glDisable(GL_BLEND);
//
//			glColor4ub(Color::WHITE.getRed(), Color::WHITE.getGreen(),
//			           Color::WHITE.getBlue(), Color::WHITE.getAlpha());
//		}
//	}

	void OpenGLDriver::drawBatchWithTextureAndColorTransform(const VertexArray &vertices,
		                                  const TextureInformation *textureInformation,
		                                  const TextureCoordinates &textureCoordinates,
		                                  const IndiceArray &indices,
		                                  const IndiceArrayList &indiceList,
		                                  const ColorArray &colors,
		                                  const ColorTransformArray &colorMultipliers,
		                                  const ColorTransformArray &colorOffsets){

        for (IndiceArrayList::const_iterator i = indiceList.begin();
			  i != indiceList.end(); ++i) {

			glEnableVertexAttribArray(attributes.color);
			glVertexAttribPointer(attributes.color, 4, GL_UNSIGNED_BYTE, GL_FALSE, 0,  GET_TEX_PTR_BATCH(colors, i->first));
			
			 

			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);


			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glEnableVertexAttribArray(attributes.vertices);
			glEnableVertexAttribArray(attributes.texCoord);

        glEnableVertexAttribArray(attributes.colorMultiplier);
        glEnableVertexAttribArray(attributes.colorOffset);


        glVertexAttribPointer(attributes.colorMultiplier, 4, GL_FLOAT, GL_FALSE, 0, GET_TEX_PTR_BATCH(colorMultipliers, i->first));
        glVertexAttribPointer(attributes.colorOffset, 4, GL_FLOAT, GL_FALSE, 0, GET_TEX_PTR_BATCH(colorOffsets, i->first));

			glVertexAttribPointer(attributes.vertices, 4, GL_FLOAT, GL_FALSE, 0, GET_PTR_BATCH(vertices, i->first));
			glVertexAttribPointer(attributes.texCoord, 4, GL_FLOAT, GL_FALSE, 0, GET_TEX_PTR_BATCH(textureCoordinates, i->first));
			
			
			if(textureInformation->colorFormat == ColorFormat::ALPHA){
                program->sendUniform("alphaFormat",GL_TRUE);

			}
			else{
                program->sendUniform("alphaFormat",GL_FALSE);
			}


			if (i == --indiceList.end()) {
				glDrawElements(GL_TRIANGLE_STRIP, static_cast<GLsizei>(indices.size() - i->second), GL_UNSIGNED_SHORT, GET_TEX_PTR_BATCH(indices, i->second));

			} else {
				glDrawElements(GL_TRIANGLE_STRIP, static_cast<GLsizei>((++IndiceArrayList::const_iterator(i))->second - i->second), GL_UNSIGNED_SHORT, GET_TEX_PTR_BATCH(indices, i->second));
			}


            glDisableVertexAttribArray(attributes.color);
			glDisableVertexAttribArray(attributes.vertices);
            glDisableVertexAttribArray(attributes.texCoord);
            glDisableVertexAttribArray(attributes.colorMultiplier);
            glDisableVertexAttribArray(attributes.colorOffset);
			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
		}
  }

//	void OpenGLDriver::drawBatchWithTextureAndColor(const VertexArray &vertices,
//	                                                const TextureInformation *textureInformation,
//	                                                const TextureCoordinates &textureCoordinates,
//	                                                const IndiceArray &indices,
//	                                                const IndiceArrayList &indiceList,
//	                                                const ColorArray &colors) {
//		for (IndiceArrayList::const_iterator i = indiceList.begin();
//		     i != indiceList.end(); ++i) {
//			glEnableVertexAttribArray(attributes.color);
//			glVertexAttribPointer(attributes.color, 4, GL_UNSIGNED_BYTE, GL_FALSE, 0,  GET_TEX_PTR_BATCH(colors, i->first));
//
//
//			glBindTexture(GL_TEXTURE_2D, textureInformation->textureId);
//
//			glEnable(GL_TEXTURE_2D);
//			glEnable(GL_BLEND);
//
//
//			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//			glEnableClientState(GL_VERTEX_ARRAY);
//			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
//
//			glVertexPointer(2, GL_FLOAT, 0, GET_PTR_BATCH(vertices, i->first));
//			glTexCoordPointer(2, GL_FLOAT, 0, GET_TEX_PTR_BATCH(textureCoordinates, i->first));
//
//             if(textureInformation->colorFormat == ColorFormat::ALPHA){
//                program->sendUniform("alphaFormat",GL_FALSE);
//
//			}
//			else{
//                program->sendUniform("alphaFormat",GL_TRUE);
//			}
//
//
//			if (i == --indiceList.end()) {
//				glDrawElements(GL_TRIANGLE_STRIP, static_cast<GLsizei>(indices.size() - i->second), GL_UNSIGNED_SHORT, GET_TEX_PTR_BATCH(indices, i->second));
//
//			} else {
//				glDrawElements(GL_TRIANGLE_STRIP, static_cast<GLsizei>((++IndiceArrayList::const_iterator(i))->second - i->second), GL_UNSIGNED_SHORT, GET_TEX_PTR_BATCH(indices, i->second));
//			}
//
//			glDisable(GL_BLEND);
//			glDisable(GL_TEXTURE_2D);
//			glDisableClientState(GL_VERTEX_ARRAY);
//			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
//			glDisableClientState(GL_COLOR_ARRAY);
//		}
//	}

//	void OpenGLDriver::drawBatchWithTexture(const VertexArray &vertices,
//	                                        const TextureInformation *textureInformation,
//	                                        const TextureCoordinates &textureCoordinates,
//	                                        const IndiceArray &indices,
//	                                        const IndiceArrayList &indiceList) {
//		for (IndiceArrayList::const_iterator i = indiceList.begin();
//		     i != indiceList.end(); ++i) {
//			glBindTexture(GL_TEXTURE_2D, textureInformation->textureId);
//
//			glEnable(GL_TEXTURE_2D);
//			glEnable(GL_BLEND);
//
//#ifdef BB_OPENGLES
//			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//#else
//			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//#endif
//
//			glEnableClientState(GL_VERTEX_ARRAY);
//			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
//
//			glVertexPointer(2, GL_FLOAT, 0, GET_PTR_BATCH(vertices, i->first));
//			glTexCoordPointer(2, GL_FLOAT, 0, GET_TEX_PTR_BATCH(textureCoordinates, i->first));
//
//			if (i == --indiceList.end()) {
//				glDrawElements(GL_TRIANGLE_STRIP, static_cast<GLsizei>(indices.size() - i->second), GL_UNSIGNED_SHORT, GET_TEX_PTR_BATCH(indices, i->second));
//
//			} else {
//				glDrawElements(GL_TRIANGLE_STRIP, static_cast<GLsizei>((++IndiceArrayList::const_iterator(i))->second - i->second), GL_UNSIGNED_SHORT, GET_TEX_PTR_BATCH(indices, i->second));
//			}
//
//			glDisable(GL_BLEND);
//			glDisable(GL_TEXTURE_2D);
//			glDisableClientState(GL_VERTEX_ARRAY);
//			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
//		}
//	}

	void OpenGLDriver::prepareScene(const Vector2 &position, float angle,
	                                const Vector2 &zoom,
	                                const Color &backgroundColor) {
		glClearColor(clampColorComponent(backgroundColor.getRed()),
		             clampColorComponent(backgroundColor.getGreen()),
		             clampColorComponent(backgroundColor.getBlue()),
		             1.0f);

		glClear(GL_COLOR_BUFFER_BIT);

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


		program = new GLSLProgram(
                    "\
					 precision mediump float;\
					uniform mat4 Projection;\
					uniform mat4 Modelview;\
					\
					attribute vec4 position;\
					attribute vec2 texcoordIN;\
                      attribute vec4 colorMultiplierIN;\
                      attribute vec4 colorOffsetIN;\
					attribute vec4 colorIN;\
								  \
					  varying vec2 texcoord;\
                      varying vec4 colorMultiplier;\
                      varying vec4 colorOffset;\
						varying vec4 color;\
								  \
                      void main(void) {\
						texcoord = texcoordIN;\
                        colorMultiplier = colorMultiplierIN;\
                        colorOffset = colorOffsetIN;\
                        color = colorIN;\
						gl_Position = Projection * Modelview * position;\
                      }"

                      ,

                      "\
					precision mediump float;\
					uniform bool  alphaFormat;\
                      uniform sampler2D  tex;\
					varying vec2 texcoord;\
					varying vec4 colorMultiplier;\
					varying vec4 colorOffset;\
					varying vec4 color;\
                      void main(void) {\
                      vec4 texColor;\
                      if(alphaFormat){ \
                        texColor = vec4(vec3(1.0), texture2D(tex, texcoord).a); \
                      } \
                      else{ \
                        texColor = texture2D(tex, texcoord); \
                      } \
                        gl_FragColor = ((color * texColor)* colorMultiplier) + vec4(colorOffset.rgb, colorOffset.a * color.a);\
                      }");

    		program->use();
			uniforms.tex = program->getUniformLocation("tex");
			uniforms.alphaFormat = program->getUniformLocation("alphaFormat");
			uniforms.projection = program->getUniformLocation("Projection");
			uniforms.modelView= program->getUniformLocation("Modelview");
		
    		program->sendUniform(uniforms.tex, 0);
            program->sendUniform(uniforms.alphaFormat, GL_FALSE);
		
			attributes.vertices = program->getAttributeLocation("position");
			attributes.texCoord = program->getAttributeLocation("texcoordIN");
            attributes.colorMultiplier = program->getAttributeLocation("colorMultiplierIN");
            attributes.colorOffset = program->getAttributeLocation("colorOffsetIN");
			attributes.color = program->getAttributeLocation("colorIN");


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
		projectionMatrix[0] = 0.5f * (right - left);
		projectionMatrix[4] = (right+left) / (right - left);
		projectionMatrix[5] = 0.5f * (top - bottom);
		projectionMatrix[8] = (top+bottom) / (top - bottom);
		projectionMatrix[10] = -1;
		projectionMatrix[12] = 0;
		projectionMatrix[15] = 1;
		
		program->sendUniform(uniforms.projection, &(projectionMatrix[0]), true);
		
#if defined(BB_MAC_PLATFORM) && defined(BB_SDL)
		int swapInterval = 1;
		CGLSetParameter(CGLGetCurrentContext(), kCGLCPSwapInterval, &swapInterval);
#endif


      //  glCreateShader(GL_VERTEX_SHADER);


		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLDriver::pushMatrix() {
	}

	
	//inspired by http://www.flashbang.se/archives/148
	void OpenGLDriver::translate(const Vector2 &translation) {

		
		tempTransformMatrix[0] = 1;
		tempTransformMatrix[1] = 0;
		tempTransformMatrix[2] = 0;
		tempTransformMatrix[3] = 0;
		
		tempTransformMatrix[4] = 0;
		tempTransformMatrix[5] = 1;
		tempTransformMatrix[6] = 0;
		tempTransformMatrix[7] = 0;
		
		tempTransformMatrix[8] = 0;
		tempTransformMatrix[9] = 0;
		tempTransformMatrix[10] = 1;
		tempTransformMatrix[11] = 0;
		
		tempTransformMatrix[12] = translation.x;
		tempTransformMatrix[13] = translation.y;
		tempTransformMatrix[14] = 0;
		tempTransformMatrix[15] = 1;
		
		multMatrix(&(modelViewMatrix[0]),&(tempTransformMatrix[0]));
	}
	
	//inspired by http://www.flashbang.se/archives/148
	void OpenGLDriver::scale(const Vector2 &scale){
		
		tempTransformMatrix[0] = scale.x;
		tempTransformMatrix[1] = 0;
		tempTransformMatrix[2] = 0;
		tempTransformMatrix[3] = 0;
		
		tempTransformMatrix[4] = 0;
		tempTransformMatrix[5] = scale.y;
		tempTransformMatrix[6] = 0;
		tempTransformMatrix[7] = 0;
		
		tempTransformMatrix[8] = 0;
		tempTransformMatrix[9] = 0;
		tempTransformMatrix[10] = 1;
		tempTransformMatrix[11] = 0;
		
		tempTransformMatrix[12] = 0;
		tempTransformMatrix[13] = 0;
		tempTransformMatrix[14] = 0;
		tempTransformMatrix[15] = 1;
		
		multMatrix(&(modelViewMatrix[0]),&(tempTransformMatrix[0]));
	}
	
	//inspired by http://www.flashbang.se/archives/148
	void OpenGLDriver::rotate(float a){
		float angle= a * MathHelper::PI_OVER_180 ;
		
		tempTransformMatrix[0] = 1;
		tempTransformMatrix[1] = -MathHelper::sin(angle);
		tempTransformMatrix[2] = 0;
		tempTransformMatrix[3] = 0;
		
		tempTransformMatrix[4] = MathHelper::sin(angle);
		tempTransformMatrix[5] = 1-(1-MathHelper::cos(angle));
		tempTransformMatrix[6] = 0;
		tempTransformMatrix[7] = 0;
		
		tempTransformMatrix[8] = 0;
		tempTransformMatrix[9] = 0;
		tempTransformMatrix[10] = 1;
		tempTransformMatrix[11] = 0;
		
		tempTransformMatrix[12] = 0;
		tempTransformMatrix[13] = 0;
		tempTransformMatrix[14] = 0;
		tempTransformMatrix[15] = 1;
		
		multMatrix(&(modelViewMatrix[0]),&(tempTransformMatrix[0]));
	}

	//inspired by http://www.flashbang.se/archives/148
	void OpenGLDriver::multMatrix(float *MatrixB,float MatrixA[16])
	{
		float NewMatrix[16];
		int i;
		for(i = 0; i < 4; i++){ //Cycle through each vector of first matrix.
			NewMatrix[i*4] = MatrixA[i*4] * MatrixB[0] + MatrixA[i*4+1] * MatrixB[4] + MatrixA[i*4+2] * MatrixB[8] + MatrixA[i*4+3] * MatrixB[12];
			NewMatrix[i*4+1] = MatrixA[i*4] * MatrixB[1] + MatrixA[i*4+1] * MatrixB[5] + MatrixA[i*4+2] * MatrixB[9] + MatrixA[i*4+3] * MatrixB[13];
			NewMatrix[i*4+2] = MatrixA[i*4] * MatrixB[2] + MatrixA[i*4+1] * MatrixB[6] + MatrixA[i*4+2] * MatrixB[10] + MatrixA[i*4+3] * MatrixB[14];
			NewMatrix[i*4+3] = MatrixA[i*4] * MatrixB[3] + MatrixA[i*4+1] * MatrixB[7] + MatrixA[i*4+2] * MatrixB[11] + MatrixA[i*4+3] * MatrixB[15];
		}
		/*this should combine the matrixes*/
		
		memcpy(MatrixB,NewMatrix,64);
	}
	
	
	//inspired by http://www.flashbang.se/archives/148
	void OpenGLDriver::loadIdentity() {
		modelViewMatrix[0] = 1;
		modelViewMatrix[1] = 0;
		modelViewMatrix[2] = 0;
		modelViewMatrix[3] = 0;
		
		modelViewMatrix[4] = 0;
		modelViewMatrix[5] = 1;
		modelViewMatrix[6] = 0;
		modelViewMatrix[7] = 0;
		
		modelViewMatrix[8] = 0;
		modelViewMatrix[9] = 0;
		modelViewMatrix[10] = 1;
		modelViewMatrix[11] = 0;
		
		modelViewMatrix[12] = 0;
		modelViewMatrix[13] = 0;
		modelViewMatrix[14] = 0;
		modelViewMatrix[15] = 1;
	}

	void OpenGLDriver::popMatrix() {
	}


	void OpenGLDriver::deleteTexture(TextureInformation *textureInfo) {
		glDeleteTextures(1, &(textureInfo->textureId));
		textureInfo->textureId = -1;
	}

	TextureInformation *OpenGLDriver::loadTexture(PixMap *pixMap) {
		GraphicDriver::loadTexture(pixMap);

		TextureInformation *texInfo = new TextureInformation();
		glGenTextures(1, &(texInfo->textureId));
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
			this->batch.render(this, this->lastTexture);
			this->lastTexture = NULL;
		}
	}

	float OpenGLDriver::clampColorComponent(unsigned short component) {
		return static_cast<float>(component) / static_cast<float>(Color::MAX_COMPONENT_VALUE);
	}

//	void OpenGLDriver::internalDrawShapeWithTextureAndColor(const VertexArray &vertices,
//	                                                        const TextureInformation *textureInformation,
//	                                                        const TextureCoordinates &textureCoordinates,
//	                                                        const Color &color) {
//		if (color.getAlpha() > 0u) {
//			glColor4ub(color.getRed(), color.getGreen(), color.getBlue(),
//			           color.getAlpha());
//
//			drawShapeWithTexture(vertices, textureInformation,
//			                     textureCoordinates);
//
//			glColor4ub(Color::WHITE.getRed(), Color::WHITE.getGreen(),
//			           Color::WHITE.getBlue(), Color::WHITE.getAlpha());
//		}
//	}
//
//	void OpenGLDriver::internalDrawShapeWithTextureAndColorTransform(const VertexArray &vertices,
//	                                                        const TextureInformation *textureInformation,
//	                                                        const TextureCoordinates &textureCoordinates,
//	                                                        const Color &color,
//	                                                        const ColorTransformArray &colorMultiplier,
//                                                            const ColorTransformArray &colorOffset) {
//
//        glVertexAttrib4f(locColorMultiplier, colorMultiplier[0], colorMultiplier[1], colorMultiplier[2], colorMultiplier[3]);
//        glVertexAttrib4f(locColorOffset, colorOffset[0], colorOffset[1], colorOffset[2], colorOffset[3]);
//
//        internalDrawShapeWithTextureAndColor(vertices, textureInformation, textureCoordinates, color);
//
//        glVertexAttrib4f(locColorMultiplier, Color::WHITE.getRed(), Color::WHITE.getGreen(), Color::WHITE.getBlue(), Color::WHITE.getAlpha());
//        glVertexAttrib4f(locColorOffset, Color::WHITE.getRed(), Color::WHITE.getGreen(), Color::WHITE.getBlue(), Color::WHITE.getAlpha());
//	}
//
	
	


	OpenGLDriver::OpenGLDriver() : GraphicDriver(), batch(), lastTexture(NULL), modelViewMatrix(16,0), tempTransformMatrix(16,0) {
	}

	OpenGLDriver::~OpenGLDriver() {

	}
}
