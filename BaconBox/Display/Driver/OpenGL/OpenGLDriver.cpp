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
		if (color.getAlpha() > 0u) {
			glColor4ub(color.getRed(), color.getGreen(), color.getBlue(),
			           color.getAlpha());

			drawShapeWithTexture(vertices, textureInformation,
			                     textureCoordinates);

			glColor4ub(Color::WHITE.getRed(), Color::WHITE.getGreen(),
			           Color::WHITE.getBlue(), Color::WHITE.getAlpha());
		}
	}

	void OpenGLDriver::drawShapeWithTexture(const VertexArray &vertices,
	                                        const TextureInformation *textureInformation,
	                                        const TextureCoordinates &textureCoordinates) {
		// We make sure the texture information is valid.
		if (textureInformation) {
			glBindTexture(GL_TEXTURE_2D, textureInformation->textureId);

			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);
#ifdef BB_OPENGLES
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#else
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#endif

			glVertexPointer(2, GL_FLOAT, 0, GET_PTR(vertices));
			glEnableClientState(GL_VERTEX_ARRAY);

			glTexCoordPointer(2, GL_FLOAT, 0, GET_TEX_PTR(textureCoordinates));
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);

			glDrawArrays(GL_TRIANGLE_STRIP, 0, static_cast<GLsizei>(vertices.getNbVertices()));

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);

		}
	}

	void OpenGLDriver::drawShapeWithColor(const VertexArray &vertices,
	                                      const Color &color) {
		if (color.getAlpha() > 0u) {
			glColor4ub(color.getRed(), color.getGreen(), color.getBlue(),
			           color.getAlpha());

			glVertexPointer(2, GL_FLOAT, 0, GET_PTR(vertices));
			glEnable(GL_BLEND);

#ifdef BB_OPENGLES
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#else
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#endif
			glEnableClientState(GL_VERTEX_ARRAY);

			glDrawArrays(GL_TRIANGLE_STRIP, 0, static_cast<GLsizei>(vertices.getNbVertices()));

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisable(GL_BLEND);

			glColor4ub(Color::WHITE.getRed(), Color::WHITE.getGreen(),
			           Color::WHITE.getBlue(), Color::WHITE.getAlpha());
		}
	}

	void OpenGLDriver::drawBatchWithTextureAndColor(const VertexArray &vertices,
	                                                const TextureInformation *textureInformation,
	                                                const TextureCoordinates &textureCoordinates,
	                                                const IndiceArray &indices,
	                                                const IndiceArrayList &indiceList,
	                                                const ColorArray &colors) {
		for (IndiceArrayList::const_iterator i = indiceList.begin();
		     i != indiceList.end(); ++i) {
			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(4,
			               GL_UNSIGNED_BYTE,
			               0,
			               GET_TEX_PTR_BATCH(colors, i->first));

			glBindTexture(GL_TEXTURE_2D, textureInformation->textureId);

			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);

#ifdef BB_OPENGLES
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#else
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#endif

			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);

			glVertexPointer(2, GL_FLOAT, 0, GET_PTR_BATCH(vertices, i->first));
			glTexCoordPointer(2, GL_FLOAT, 0, GET_TEX_PTR_BATCH(textureCoordinates, i->first));

			if (i == --indiceList.end()) {
				glDrawElements(GL_TRIANGLE_STRIP, static_cast<GLsizei>(indices.size() - i->second), GL_UNSIGNED_SHORT, GET_TEX_PTR_BATCH(indices, i->second));

			} else {
				glDrawElements(GL_TRIANGLE_STRIP, static_cast<GLsizei>((++IndiceArrayList::const_iterator(i))->second - i->second), GL_UNSIGNED_SHORT, GET_TEX_PTR_BATCH(indices, i->second));
			}

			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			glDisableClientState(GL_COLOR_ARRAY);
		}
	}

	void OpenGLDriver::drawBatchWithTexture(const VertexArray &vertices,
	                                        const TextureInformation *textureInformation,
	                                        const TextureCoordinates &textureCoordinates,
	                                        const IndiceArray &indices,
	                                        const IndiceArrayList &indiceList) {
		for (IndiceArrayList::const_iterator i = indiceList.begin();
		     i != indiceList.end(); ++i) {
			glBindTexture(GL_TEXTURE_2D, textureInformation->textureId);

			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);

#ifdef BB_OPENGLES
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#else
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#endif

			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);

			glVertexPointer(2, GL_FLOAT, 0, GET_PTR_BATCH(vertices, i->first));
			glTexCoordPointer(2, GL_FLOAT, 0, GET_TEX_PTR_BATCH(textureCoordinates, i->first));

			if (i == --indiceList.end()) {
				glDrawElements(GL_TRIANGLE_STRIP, static_cast<GLsizei>(indices.size() - i->second), GL_UNSIGNED_SHORT, GET_TEX_PTR_BATCH(indices, i->second));

			} else {
				glDrawElements(GL_TRIANGLE_STRIP, static_cast<GLsizei>((++IndiceArrayList::const_iterator(i))->second - i->second), GL_UNSIGNED_SHORT, GET_TEX_PTR_BATCH(indices, i->second));
			}

			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		}
	}

void OpenGLDriver::prepareScene(const Vector2 &position, float angle,
	                                const Vector2 &zoom,
	                                const Color &backgroundColor) {
		glClearColor(clampColorComponent(backgroundColor.getRed()),
		             clampColorComponent(backgroundColor.getGreen()),
		             clampColorComponent(backgroundColor.getBlue()),
		             1.0f);

		glClear(GL_COLOR_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		switch (MainWindow::getInstance().getOrientation().underlying()) {
		case WindowOrientation::HORIZONTAL_LEFT:
			glRotatef(-90.0f, 0, 0, 1);
			glTranslatef(-static_cast<float>(MainWindow::getInstance().getContextWidth()), 0.0f, 0.0f);
			break;

		case WindowOrientation::HORIZONTAL_RIGHT:
			glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
			glTranslatef(0.0f, -static_cast<float>(MainWindow::getInstance().getContextHeight()), 0.0f);
			break;

		default:
			break;
		}

		glScalef(zoom.x, zoom.y, 1);
		glRotatef(angle, 0, 0, 1);
		glTranslatef(-(position.x), -(position.y), 0);

	}

void OpenGLDriver::initializeGraphicDriver() {
		GraphicDriver::initializeGraphicDriver();
		glShadeModel(GL_FLAT);

		if (MainWindow::getInstance().getOrientation() == WindowOrientation::NORMAL ||
		    MainWindow::getInstance().getOrientation() == WindowOrientation::UPSIDE_DOWN) {
			glViewport(0, 0, static_cast<int>(MainWindow::getInstance().getResolutionWidth()), static_cast<int>(MainWindow::getInstance().getResolutionHeight()));

		} else {
			glViewport(0, 0, static_cast<int>(MainWindow::getInstance().getResolutionHeight()), static_cast<int>(MainWindow::getInstance().getResolutionWidth()));
		}

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

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

#ifdef BB_OPENGLES
		glOrthof(left, right, bottom, top, -1.0f, 1.0f);
#else
		glOrtho(static_cast<double>(left), static_cast<double>(right), static_cast<double>(bottom), static_cast<double>(top), -1.0, 1.0);
#endif
#if defined(BB_MAC_PLATFORM) && defined(BB_SDL)
		int swapInterval = 1;
		CGLSetParameter(CGLGetCurrentContext(), kCGLCPSwapInterval, &swapInterval);
#endif


		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLDriver::pushMatrix() {
		glPushMatrix();
	}

	void OpenGLDriver::translate(const Vector2 &translation) {
		glTranslatef(-translation.x, -translation.y, 0.0f);
	}

	void OpenGLDriver::loadIdentity() {
		glLoadIdentity();
	}

	void OpenGLDriver::popMatrix() {
		glPopMatrix();
	}
    
    
    void OpenGLDriver::deleteTexture(TextureInformation * textureInfo){
        glDeleteTextures(1, &(textureInfo->textureId));
	textureInfo->textureId = -1;
    }

	TextureInformation *OpenGLDriver::loadTexture(PixMap *pixMap) {
	    GraphicDriver::loadTexture(pixMap);

		TextureInformation *texInfo = new TextureInformation();
		glGenTextures(1, &(texInfo->textureId));
		glBindTexture(GL_TEXTURE_2D, texInfo->textureId);


		int widthPoweredToTwo = MathHelper::nextPowerOf2(pixMap->getWidth());
		int heightPoweredToTwo = MathHelper::nextPowerOf2(pixMap->getHeight());


		PixMap poweredTo2Pixmap(widthPoweredToTwo, heightPoweredToTwo, pixMap->getColorFormat());
		poweredTo2Pixmap.insertSubPixMap(*pixMap);


		texInfo->imageWidth = pixMap->getWidth();
		texInfo->imageHeight = pixMap->getHeight();

		texInfo->poweredWidth = widthPoweredToTwo;
		texInfo->poweredHeight = heightPoweredToTwo;

		GLint format;
		texInfo->colorFormat = pixMap->getColorFormat();

		if (pixMap->getColorFormat() == ColorFormat::RGBA) {
			format = GL_RGBA;

		} else { // if (pixMap->getColorFormat() == ColorFormat::ALPHA)
			format = GL_ALPHA;
		}

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

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		return texInfo;
	}

	float OpenGLDriver::clampColorComponent(unsigned short component) {
		return static_cast<float>(component) / static_cast<float>(Color::MAX_COMPONENT_VALUE);
	}

	OpenGLDriver::OpenGLDriver() : GraphicDriver() {
	}

	OpenGLDriver::~OpenGLDriver() {
		
	}
}
