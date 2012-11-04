#include "SDLMainWindow.h"

#include <iostream>
// ===== BEGIN TO REMOVE EVENTUALLY =====
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
// ===== END TO REMOVE EVENTUALLY =====

#include "PlatformFlagger.h"

#include "Engine.h"

namespace BaconBox {

	void SDLMainWindow::onBaconBoxInit(unsigned int resolutionWidth, unsigned int resolutionHeight, float contextWidth, float contextHeight) {
		this->MainWindow::setResolution(resolutionWidth, resolutionHeight);
		this->MainWindow::setContextSize(contextWidth, contextHeight);

		mainWindow = SDL_CreateWindow(Engine::getApplicationName().c_str(),
		                              SDL_WINDOWPOS_CENTERED,
		                              SDL_WINDOWPOS_CENTERED,
		                              static_cast<int>(this->getResolutionWidth()),
		                              static_cast<int>(this->getResolutionHeight()),
		                              SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		mainContext = SDL_GL_CreateContext(mainWindow);

		if (SDL_GL_SetSwapInterval(1) < 0) {
			std::cout << "OpenGL error [SetSwapInterval]: " << SDL_GetError() << std::endl;
		}
	}

	void SDLMainWindow::show() {
		bool running = true;
		SDL_Event event;
		
		while (running) {
			SDL_PollEvent(&event);
			
			if (event.type == SDL_QUIT) {
				running = false;
			}
			
			Engine::pulse();

			if (!Engine::isBufferSwapped()) {
				SDL_GL_SwapWindow(mainWindow);
				Engine::setBufferSwapped();
			}
		}
	}

	void SDLMainWindow::setResolution(unsigned int resolutionWidth,
	                                  unsigned int resolutionHeight) {
		this->MainWindow::setResolution(resolutionWidth, resolutionHeight);
		
		SDL_SetWindowSize(mainWindow, static_cast<int>(this->getResolutionWidth()), static_cast<int>(this->getResolutionHeight()));

		// ===== BEGIN TO REMOVE EVENTUALLY =====
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
			
		} else if (MainWindow::getInstance().getOrientation() == WindowOrientation::HORIZONTAL_RIGHT) {
			left = static_cast<float>(MainWindow::getInstance().getContextHeight());
			right = 0.0f;
			bottom = 0.0f;
			top = static_cast<float>(MainWindow::getInstance().getContextWidth());
		}
		
		glOrtho(static_cast<double>(left), static_cast<double>(right), static_cast<double>(bottom), static_cast<double>(top), -1.0, 1.0);
		int swapInterval = 1;
		CGLSetParameter(CGLGetCurrentContext(), kCGLCPSwapInterval, &swapInterval);
		
		//FBO and mask texture initialization
		GLint tempBuffer;
		glGetIntegerv(GL_FRAMEBUFFER_BINDING_EXT, &tempBuffer);
		
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		
		glClear(GL_COLOR_BUFFER_BIT);
		// ===== END TO REMOVE EVENTUALLY =====
	}

	void SDLMainWindow::setContextSize(float newContextWidth,
	                                   float newContextHeight) {
		this->MainWindow::setContextSize(newContextWidth, newContextHeight);
		
		// ===== BEGIN TO REMOVE EVENTUALLY =====
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
			
		} else if (MainWindow::getInstance().getOrientation() == WindowOrientation::HORIZONTAL_RIGHT) {
			left = static_cast<float>(MainWindow::getInstance().getContextHeight());
			right = 0.0f;
			bottom = 0.0f;
			top = static_cast<float>(MainWindow::getInstance().getContextWidth());
		}
		
		glOrtho(static_cast<double>(left), static_cast<double>(right), static_cast<double>(bottom), static_cast<double>(top), -1.0, 1.0);
		int swapInterval = 1;
		CGLSetParameter(CGLGetCurrentContext(), kCGLCPSwapInterval, &swapInterval);
		
		//FBO and mask texture initialization
		GLint tempBuffer;
		glGetIntegerv(GL_FRAMEBUFFER_BINDING_EXT, &tempBuffer);
		
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		
		glClear(GL_COLOR_BUFFER_BIT);
		// ===== END TO REMOVE EVENTUALLY =====
	}

	void SDLMainWindow::setCaption(const std::string &caption) {
		SDL_SetWindowTitle(mainWindow, caption.c_str());
	}

	bool SDLMainWindow::isFullScreen() const {
		return static_cast<bool>(SDL_GetWindowFlags(mainWindow) & SDL_WINDOW_FULLSCREEN);
	}

	void SDLMainWindow::setFullScreen(bool newFullScreen) {
		SDL_SetWindowFullscreen(mainWindow, ((newFullScreen) ? (SDL_TRUE) : (SDL_FALSE)));
	}

	bool SDLMainWindow::isInputGrabbed() const {
		return static_cast<bool>(SDL_GetWindowFlags(mainWindow) & SDL_WINDOW_INPUT_GRABBED);
	}

	void SDLMainWindow::setInputGrabbed(bool newInputGrabbed) {
		SDL_SetWindowGrab(mainWindow, ((newInputGrabbed) ? (SDL_TRUE) : (SDL_FALSE)));
	}

	SDLMainWindow::SDLMainWindow() : MainWindow(), mainWindow(NULL),
		mainContext(NULL) {

        SDL_Init(SDL_INIT_VIDEO);
            
		if (SDL_GL_SetAttribute(SDL_GL_RED_SIZE,   8) < 0) {
			std::cout << "opengl error: " << SDL_GetError() << std::endl;
		}

		if (SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,  8) < 0) {
			std::cout << "opengl error: " << SDL_GetError() << std::endl;
		}

		if (SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8) < 0) {
			std::cout << "opengl error: " << SDL_GetError() << std::endl;
		}

		if (SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8) < 0) {
			std::cout << "opengl error: " << SDL_GetError() << std::endl;
		}

		if (SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,  32) < 0) {
			std::cout << "opengl error: " << SDL_GetError() << std::endl;
		}

		if (SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,  1) < 0) {
			std::cout << "Couldn't set double buffering: " << SDL_GetError() << std::endl;
		}
	}

	SDLMainWindow::~SDLMainWindow() {
		if (mainContext) {
			SDL_GL_DeleteContext(mainContext);
			SDL_DestroyWindow(mainWindow);
		}

		SDL_Quit();
	}
    
    void SDLMainWindow::hideCursor(){
        SDL_ShowCursor(SDL_DISABLE);
    }
    
    void SDLMainWindow::showCursor(){
        SDL_ShowCursor(SDL_ENABLE);
    }
}
