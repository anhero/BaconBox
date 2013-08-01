#include "BaconBox/PlatformFlagger.h"

#include "BaconBox/Core/BaseEngine.h"
#include "BaconBox/Core/Engine.h"

#include <cassert>
#include <cstdlib>

#include <algorithm>

#include "BaconBox/Helper/TimeHelper.h"
#include "BaconBox/Display/Driver/GraphicDriver.h"
#include "BaconBox/Helper/DeleteHelper.h"

#ifndef BB_ANDROID
#include "BaconBox/Display/Text/Font.h"
#endif

#include "BaconBox/Audio/AudioEngine.h"
#include "BaconBox/Audio/SoundEngine.h"
#include "BaconBox/Audio/MusicEngine.h"
#include "BaconBox/Input/InputManager.h"
#include "BaconBox/Helper/TimerManager.h"
#include "BaconBox/ResourceManager.h"
#include "BaconBox/Console.h"
#include <libgen.h>

#include BB_MAIN_WINDOW_INCLUDE
#include BB_SOUND_ENGINE_INCLUDE
#include BB_MUSIC_ENGINE_INCLUDE
#include BB_GRAPHIC_DRIVER_INCLUDE

namespace BaconBox {


	void BaseEngine::application(int argc, char *argv[], const std::string &name) {
		this->argc = argc;
		this->argv = argv;
		if(argv)this->applicationPath = dirname(argv[0]);
		this->applicationName = name;
	}

	State *BaseEngine::addState(State *newState) {
		if (newState) {
			if (this->states.empty()) {
				assert(!this->currentState);
				this->nextState = newState;
			}

			this->states.insert(std::pair<std::string, State *>(newState->getName(), newState));
		}

		return newState;
	}

	State *BaseEngine:: getState(const std::string &name){
	    std::map<std::string, State *>::iterator i = this->states.find(name);
	    return i->second;
	}


	void BaseEngine::removeState(const std::string &name) {
		std::map<std::string, State *>::iterator toDelete = this->states.find(name);

		if (this->nextState != toDelete->second) {
			if (toDelete->second) {
				delete toDelete->second;
			}

			this->states.erase(toDelete);
		}
		this->currentState = NULL;
	}

	void BaseEngine::removeAllStates() {
		if(this->currentState)this->currentState->internalOnLoseFocus();

	    std::list<std::string> statesNames;
		for(std::map<std::string, State *>::iterator i= this->states.begin();
			i!= this->states.end(); i++){
		    statesNames.push_back(i->first);
		}

		for(std::list<std::string>::iterator i= statesNames.begin();
			i!= statesNames.end(); i++){
		    removeState(*i);
		}
	}

	State *BaseEngine::playState(const std::string &name) {
		// We make sure the state asked for exists.
		std::map<std::string, State *>::iterator it = this->states.find(name);

		if (it != this->states.end()) {
			this->nextState = it->second;

		} else {
			Console::println("State \"" + name +
			                 "\" doesn't exist so it cannot be played.");
		}

		return this->nextState;
	}

	State *BaseEngine::getCurrentState() {
		return this->currentState;
	}

	unsigned int BaseEngine::getMinFps() {
		return this->minFps;
	}

	double BaseEngine::getUpdatesPerSecond() {
		assert(this->updateDelay);
		return 1.0 / this->updateDelay;
	}

	double BaseEngine::getUpdateDelay() {
		return this->updateDelay;
	}

	void BaseEngine::setMinFps(unsigned int newMinFps) {
		this->minFps = newMinFps;
	}

	void BaseEngine::setUpdatesPerSecond(double updatesPerSecond) {
		if (updatesPerSecond) {
			// Calculate the update delay.
			this->updateDelay = 1.0 / static_cast<double>(updatesPerSecond);
		}
	}

	void BaseEngine::switchToNextState(){
	    if (this->nextState) {
					// If the next state is the first state the engine is
					// playing, the current state will be set to NULL, so we
					// call the onLoseFocus only if the currentState is valid.
					if (this->currentState) {
						this->currentState->internalOnLoseFocus();
					}

					// We set the next state as the current state.
					this->currentState = this->nextState;
					// We call the onGetFocus method.
					this->currentState->internalOnGetFocus();

					this->nextState = NULL;
				}

	}


	void BaseEngine::pulse() {
		// We make sure the pointer to the current state is valid.
		if (this->currentState || this->nextState) {
			TimeHelper::getInstance().refreshTime();

			
			InputManager::getInstance().update();
			    if(! this->currentState && this->nextState){
				switchToNextState();
			    }
				this->currentState->internalUpdate();
				GraphicDriver::getInstance().finalizeRender();
				this->renderedSinceLastUpdate = true;
				this->bufferSwapped = false;
				this->lastRender = TimeHelper::getInstance().getSinceStartComplete();

			if (static_cast<AudioEngine *>(this->soundEngine) != static_cast<AudioEngine *>(this->musicEngine)) {
				this->soundEngine->update();
			}

			this->musicEngine->update();
		}

		if (this->needsExit) {
			exit(this->tmpExitCode);
		}
	}

	void BaseEngine::initializeEngine(unsigned int resolutionWidth,
	                              unsigned int resolutionHeight,
	                              float contextWidth,
	                              float contextHeight, WindowOrientation::type orientation) {

		TimeHelper::getInstance();
		InputManager::getInstance();
		Engine::onInitialize.shoot(resolutionWidth, resolutionHeight, contextWidth, contextHeight, orientation);

		this->graphicDriver->initializeGraphicDriver();
	}

	double BaseEngine::getSinceLastUpdate() {
		return (this->lastUpdate) ? (TimeHelper::getInstance().getSinceStartComplete() - this->lastUpdate) : (this->lastUpdate);
	}

	double BaseEngine::getSinceLastRender() {
		return (this->lastRender) ? (TimeHelper::getInstance().getSinceStartComplete() - this->lastRender) : (this->lastRender);
	}

	bool BaseEngine::isBufferSwapped() {
		return this->bufferSwapped;
	}

	void BaseEngine::setBufferSwapped() {
		this->bufferSwapped = true;
	}

	void BaseEngine::exitApplication(int exitCode) {
		this->needsExit = true;
		this->tmpExitCode = exitCode;
	}

	void BaseEngine::showMainWindow() {
		MainWindow::getInstance().show();
	}

	const std::string &BaseEngine::getApplicationPath() {
		return this->applicationPath;
	}

	const std::string &BaseEngine::getApplicationName() {
		return this->applicationName;
	}

	int &BaseEngine::getApplicationArgc() {
		return this->argc;
	}

	char **BaseEngine::getApplicationArgv() {
		return this->argv;
	}

	MainWindow &BaseEngine::getMainWindow() {
		return *this->mainWindow;
	}

	GraphicDriver &BaseEngine::getGraphicDriver() {
		return *this->graphicDriver;
	}

	SoundEngine &BaseEngine::getSoundEngine() {
		return *this->soundEngine;
	}

	MusicEngine &BaseEngine::getMusicEngine() {
		return *this->musicEngine;
	}

	BaseEngine::BaseEngine() : currentState(NULL), nextState(NULL) , lastUpdate(0.0), lastRender(0.0),
	loops(0), nextUpdate(0), updateDelay(1.0 / Engine::DEFAULT_UPDATES_PER_SECOND),
	minFps(Engine::DEFAULT_MIN_FRAMES_PER_SECOND), bufferSwapped(false), needsExit(false),
	tmpExitCode(0), renderedSinceLastUpdate(true), applicationPath(),
	applicationName(Engine::DEFAULT_APPLICATION_NAME), mainWindow(NULL),
	graphicDriver(NULL), soundEngine(NULL), musicEngine(NULL) {

		mainWindow = BB_MAIN_WINDOW_IMPL;
		graphicDriver = BB_GRAPHIC_DRIVER_IMPL;
		soundEngine = BB_SOUND_ENGINE_IMPL;
		musicEngine = BB_MUSIC_ENGINE_IMPL;
	}

	BaseEngine::~BaseEngine() {
		// We delete the states.
		std::for_each(states.begin(), states.end(), DeletePointerFromPair());

		// We unload the resources.
		ResourceManager::unloadAll();

		// We unload the audio engines.
		if (static_cast<AudioEngine *>(musicEngine) == static_cast<AudioEngine *>(soundEngine)) {
			delete musicEngine;

		} else {
			if (musicEngine) {
				delete musicEngine;
			}

			if (soundEngine) {
				delete soundEngine;
			}
		}

		// We unload the graphic driver;
		if (graphicDriver) {
			delete graphicDriver;
		}

		// We unload the main window;
		if (mainWindow) {
			delete mainWindow;
		}
	}
}
