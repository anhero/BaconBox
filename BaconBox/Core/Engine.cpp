#include "Engine.h"

#include <cassert>
#include <cstdlib>

#include <iostream>
#include <algorithm>
// ===== BEGIN TO REMOVE EVENTUALLY =====
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
// ===== END TO REMOVE EVENTUALLY =====

#include "MainWindow.h"
#include "PlatformFlagger.h"
#include "TimeHelper.h"
#include "DeleteHelper.h"

#include <libgen.h>

#include "State.h"

#include BB_MAIN_WINDOW_INCLUDE

namespace BaconBox {
	const double Engine::DEFAULT_UPDATES_PER_SECOND = 60.0;
	const std::string Engine::DEFAULT_APPLICATION_NAME = std::string("BaconBoxApp");

	int Engine::argc;
	char **Engine::argv;

	void Engine::application(int argc, char *argv[], const std::string &name) {
		Engine::argc = argc;
		Engine::argv = argv;
		getInstance().applicationPath = dirname(argv[0]);
		getInstance().applicationName = name;
	}

	State *Engine::addState(State *newState) {
		Engine &engine = getInstance();

		if (newState) {
			if (engine.states.empty()) {
				assert(!engine.currentState);
				engine.nextState = newState;
			}

			engine.states.insert(std::pair<std::string, State *>(newState->getName(), newState));
		}

		return newState;
	}

	void Engine::removeState(const std::string &name) {
		Engine &engine = getInstance();
		std::map<std::string, State *>::iterator toDelete = engine.states.find(name);

		if (engine.currentState != toDelete->second) {
			if (toDelete->second) {
				delete toDelete->second;
			}

			engine.states.erase(toDelete);
		}
	}

	State *Engine::playState(const std::string &name) {
		Engine &engine = getInstance();
		// We make sure the state asked for exists.
		std::map<std::string, State *>::iterator it = engine.states.find(name);

		if (it != engine.states.end()) {
			engine.nextState = it->second;

		} else {
			std::cout << "State \"" << name << "\" doesn't exist so it cannot be played." << std::endl;
		}

		return engine.nextState;
	}

	State *Engine::getCurrentState() {
		return getInstance().currentState;
	}

	unsigned int Engine::getMinFps() {
		return getInstance().minFps;
	}

	double Engine::getUpdatesPerSecond() {
		assert(getInstance().updateDelay);
		return 1.0 / getInstance().updateDelay;
	}

	double Engine::getUpdateDelay() {
		return getInstance().updateDelay;
	}

	void Engine::setMinFps(unsigned int newMinFps) {
		getInstance().minFps = newMinFps;
	}

	void Engine::setUpdatesPerSecond(double updatesPerSecond) {
		if (updatesPerSecond) {
			// Calculate the update delay.
			getInstance().updateDelay = 1.0 / static_cast<double>(updatesPerSecond);
		}
	}

	void Engine::pulse() {
		Engine &engine = getInstance();

		// We make sure the pointer to the current state is valid.
		if (engine.currentState || engine.nextState) {
			TimeHelper::getInstance().refreshTime();

			// We update the time from TimeHelper.
			if (!engine.nextUpdate) {
				engine.nextUpdate = TimeHelper::getInstance().getSinceStartComplete();
			}

			engine.loops = 0;

			while (TimeHelper::getInstance().getSinceStartComplete() > engine.nextUpdate &&
			       engine.loops < engine.minFps) {
				// We refresh the time.
				TimeHelper::getInstance().refreshTime();

				// We call the focus methods if needed.
				if (engine.nextState) {
					// If the next state is the first state the engine is
					// playing, the current state will be set to NULL, so we
					// call the onLoseFocus only if the currentState is valid.
					if (engine.currentState) {
						engine.currentState->internalOnLoseFocus();
					}

					// We set the next state as the current state.
					engine.currentState = engine.nextState;
					// We call the onGetFocus method.
					engine.currentState->internalOnGetFocus();

					engine.nextState = NULL;
				}

				// We update the current state.
				engine.currentState->internalUpdate();

				engine.renderedSinceLastUpdate = false;
				engine.nextUpdate += engine.updateDelay;
				engine.lastUpdate = TimeHelper::getInstance().getSinceStartComplete();
				++engine.loops;
			}

			if (!engine.renderedSinceLastUpdate) {
				engine.currentState->internalRender();
				// ===== BEGIN TO REMOVE EVENTUALLY =====
				glClearColor(0.0f,
							 0.0f,
							 0.0f,
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
				
				glScalef(1.0f, 1.0f, 1);
				glRotatef(0.0f, 0, 0, 1);
				glTranslatef(0.0f, 0.0f, 0);
				// ===== END TO REMOVE EVENTUALLY =====
				engine.renderedSinceLastUpdate = true;
				engine.bufferSwapped = false;
				engine.lastRender = TimeHelper::getInstance().getSinceStartComplete();
			}
		}

		if (engine.needsExit) {
			exit(engine.tmpExitCode);
		}
	}

	void Engine::initializeEngine(unsigned int resolutionWidth,
	                              unsigned int resolutionHeight,
	                              float contextWidth,
	                              float contextHeight) {
		TimeHelper::getInstance();
		MainWindow::getInstance().onBaconBoxInit(resolutionWidth, resolutionHeight, contextWidth, contextHeight);
	}

	double Engine::getSinceLastUpdate() {
		Engine &engine = getInstance();
		return (engine.lastUpdate) ? (TimeHelper::getInstance().getSinceStartComplete() - engine.lastUpdate) : (engine.lastUpdate);
	}

	double Engine::getSinceLastRender() {
		Engine &engine = getInstance();
		return (engine.lastRender) ? (TimeHelper::getInstance().getSinceStartComplete() - engine.lastRender) : (engine.lastRender);
	}

	bool Engine::isBufferSwapped() {
		return getInstance().bufferSwapped;
	}

	void Engine::setBufferSwapped() {
		getInstance().bufferSwapped = true;
	}

	void Engine::exitApplication(int exitCode) {
		getInstance().needsExit = true;
		getInstance().tmpExitCode = exitCode;
	}

	void Engine::showMainWindow() {
		MainWindow::getInstance().show();
	}

	const std::string &Engine::getApplicationPath() {
		return getInstance().applicationPath;
	}

	const std::string &Engine::getApplicationName() {
		return getInstance().applicationName;
	}

	int &Engine::getApplicationArgc() {
		return Engine::argc;
	}

	char **Engine::getApplicationArgv() {
		return Engine::argv;
	}

	MainWindow &Engine::getMainWindow() {
		return *getInstance().mainWindow;
	}

	Engine &Engine::getInstance() {
		static Engine instance;
		return instance;
	}

	Engine::Engine() : currentState(NULL), nextState(NULL) , lastUpdate(0.0), lastRender(0.0),
		loops(0), nextUpdate(0), updateDelay(1.0 / DEFAULT_UPDATES_PER_SECOND),
		minFps(DEFAULT_MIN_FRAMES_PER_SECOND), bufferSwapped(false), needsExit(false),
		tmpExitCode(0), renderedSinceLastUpdate(true), applicationPath(),
		applicationName(DEFAULT_APPLICATION_NAME), mainWindow(NULL) {

		mainWindow = BB_MAIN_WINDOW_IMPL;
	}

	Engine::~Engine() {
		// We delete the states.
		std::for_each(states.begin(), states.end(), DeletePointerFromPair());

		// We unload the main window;
		if (mainWindow) {
			delete mainWindow;
		}
	}
}
