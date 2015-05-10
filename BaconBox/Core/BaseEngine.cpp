#include "BaconBox/PlatformFlagger.h"

#include "BaconBox/Core/BaseEngine.h"
#include "BaconBox/Core/Engine.h"

#include <cassert>
#include <cstdlib>

#include <algorithm>

#include "BaconBox/Helper/TimeHelper.h"

#ifdef BB_USE_STANDARD_RENDERER
#include "BaconBox/Display/StandardRenderer/Driver/GraphicDriver.h"
#endif

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
#include <signal.h>
#include "BaconBox/Display/Window/MainWindow.h"

#ifdef BB_LUA
#include "BaconBox/Script/Lua/LuaManager.h"
#endif //BB_LUA

namespace BaconBox {
	
#if defined(BB_LUA) && defined(BB_DEBUG) && !defined(BB_WINDOWS_PLATFORM)
	void
	handler (int cause, siginfo_t * info, void *uap)
	{
		BaconBox::LuaManager::error("SEGFAULT/SIGBUS/SIGILL", true);
	}
#endif //defined(BB_LUA) && defined(BB_DEBUG)
	
	void BaseEngine::application(int argc, char *argv[], const std::string &name) {

		// POSIX Signal handler.
#if defined(BB_LUA) && defined(BB_DEBUG) && !defined(BB_ANDROID) && !defined(BB_WINDOWS_PLATFORM)
		struct sigaction sa;
		sa.sa_sigaction = handler;
		sigemptyset (&sa.sa_mask);
		sa.sa_flags = SA_SIGINFO;
		 if (sigaction (SIGBUS, &sa, 0)) {
		 	perror ("sigaction");
		 	exit(1);
		 }
		 if (sigaction (SIGSEGV, &sa, 0)) {
		 	perror ("sigaction");
		 	exit(1);
		 }
		 if (sigaction (SIGILL, &sa, 0)) {
		 	perror ("sigaction");
		 	exit(1);
		 }
//		for(int i = 1; i < 32; i++){
//			struct sigaction sa;
//			sa.sa_sigaction = handler;
//			sigemptyset (&sa.sa_mask);
//			sa.sa_flags = SA_SIGINFO;
//			if (sigaction (i, &sa, 0)) {
//				perror ("sigaction");
//				exit(1);
//			}		
//		}

		
#endif //defined(BB_LUA) && defined(BB_DEBUG)
		this->argc = argc;
		this->argv = argv;

		if (argv) {
			this->applicationPath = dirname(argv[0]);
		}

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
		if(this->currentState == toDelete->second){
			this->currentState->internalOnLoseFocus();
			this->currentState = NULL;
		}
		if (this->nextState != toDelete->second) {
			if (toDelete->second) {
				delete toDelete->second;
			}

			this->states.erase(toDelete);
		}
		
	}

	void BaseEngine::removeAllStates() {

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
		getMainWindow().setUpdatesPerSecond(updatesPerSecond);
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
			
			// We update the time from TimeHelper.
			if (!this->nextUpdate) {
				this->nextUpdate = TimeHelper::getInstance().getSinceStartComplete();
			}
			
			this->loops = 0;
			
			if (TimeHelper::getInstance().getSinceStartComplete() > this->nextUpdate &&
			       this->loops < this->minFps) {
				// We refresh the time.
				TimeHelper::getInstance().refreshTime();
				
				// We call the focus methods if needed.
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
				
				// We update the current state.
				this->currentState->internalUpdate();
				
				this->renderedSinceLastUpdate = false;
				// We update the input manager.
				InputManager::getInstance().update();
				// We update the timers.
				TimerManager::update();
				this->lastUpdate = TimeHelper::getInstance().getSinceStartComplete();
#ifdef BB_IPHONE_PLATFORM
				this->nextUpdate += this->updateDelay; //This will make the engine try to catch back if it falls behind
#else
				this->nextUpdate = this->lastUpdate + this->updateDelay; //This one won't try to catch back.
#endif
				++this->loops;
			}
			
			if (!this->renderedSinceLastUpdate) {
//				this->currentState->internalRender();
				#ifdef BB_USE_STANDARD_RENDERER
					GraphicDriver::getInstance().finalizeRender();
				#endif
				this->renderedSinceLastUpdate = true;
				this->bufferSwapped = false;
				this->lastRender = TimeHelper::getInstance().getSinceStartComplete();
			}
			
			// TODO : Update logic to de-hardcode checking for SoundEngine equal to MusicEngine, and do /the right thing™/
			if (static_cast<AudioEngine *>( &(this->getSoundEngine()) ) != static_cast<AudioEngine *>( &(this->getMusicEngine()) )) {
				this->getSoundEngine().update();
			}
			
			this->getMusicEngine().update();
		}
		
		if (this->needsExit) {
			exit(this->tmpExitCode);
		}
	}

	void BaseEngine::initializeEngine(unsigned int resolutionWidth,
	                              unsigned int resolutionHeight,
	                              float contextWidth,
	                              float contextHeight, WindowOrientation::type orientation) {
		// FIXME : Move to Singleton classes...
		TimeHelper::getInstance();
		InputManager::getInstance();

		// Engine::onInitialize.shoot(resolutionWidth, resolutionHeight, contextWidth, contextHeight, orientation);
		MainWindow::getInstance().onBaconBoxInit(resolutionWidth, resolutionHeight, contextWidth, contextHeight, orientation);
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

	// Singleton instance getters
	// TODO : Deprecate/remove?

	MainWindow &BaseEngine::getMainWindow() {
		return MainWindow::getInstance();
	}
#ifdef BB_USE_STANDARD_RENDERER
	GraphicDriver &BaseEngine::getGraphicDriver() {
		return GraphicDriver::getInstance();
	}
#endif
	SoundEngine &BaseEngine::getSoundEngine() {
		return SoundEngine::getInstance();
	}

	MusicEngine &BaseEngine::getMusicEngine() {
		return MusicEngine::getInstance();
	}

	void BaseEngine::registerSingleton(Singleton * singleton) {
		PRLN("Registering `" + singleton->getName() + "` singleton.");
		std::deque<Singleton * >::iterator
			searchIt = std::find(singletons.begin(), singletons.end(), singleton);
		if (searchIt != singletons.end()) {
			PRLN("WARNING : Adding a Singleton already registered!! (" + singleton->getName() + ")");
			PV(singleton);
			return;
		}
		singletons.push_back(singleton);
	}

	void BaseEngine::destroySingleton (Singleton * toDelete) {
		std::deque<Singleton * >::iterator
			searchIt = std::find(singletons.begin(), singletons.end(), toDelete);
		if (searchIt == singletons.end()) {
			PRLN("WARNING : Trying to erase Singleton which is not registered.");
			PV(toDelete);
		}
		singletons.erase(searchIt, ++searchIt);
		toDelete->destroyInstance();
	}
	void BaseEngine::destroyAllSingletons() {
		while (!singletons.empty()) {
			PRLN("Detroying `" + singletons.back()->getName() + "` singleton.");
			singletons.back()->destroyInstance();
			singletons.pop_back();
		}
	}

	BaseEngine::BaseEngine() : currentState(NULL), nextState(NULL) , lastUpdate(0.0), lastRender(0.0),
	loops(0), nextUpdate(0), updateDelay(1.0 / Engine::DEFAULT_UPDATES_PER_SECOND),
	minFps(Engine::DEFAULT_MIN_FRAMES_PER_SECOND), bufferSwapped(false), needsExit(false),
	tmpExitCode(0), renderedSinceLastUpdate(true), applicationPath(),
	applicationName(Engine::DEFAULT_APPLICATION_NAME) {
		Engine::setInstance(*this);

	}

	BaseEngine::~BaseEngine() {
		// We delete the states.
		std::for_each(states.begin(), states.end(), DeletePointerFromPair());

		// We unload the resources.
		ResourceManager::deleteAll();

		destroyAllSingletons();

		Engine::setInstance(*(BaseEngine*)NULL);
	}
}
