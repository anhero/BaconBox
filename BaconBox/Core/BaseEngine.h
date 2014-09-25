
#ifndef BB_BASE_ENGINE_H
#define BB_BASE_ENGINE_H

#include <map>
#include <string>
#include <sigly.h>
#include "BaconBox/PlatformFlagger.h"
#include "BaconBox/Core/State.h"
#include "BaconBox/Display/Window/WindowOrientation.h"
#include "BaconBox/Core/Singleton.h"

namespace BaconBox {
	class MainWindow;
	#ifdef BB_USE_STANDARD_RENDERER
	class GraphicDriver;
	#endif
	class SoundEngine;
	class MusicEngine;
	
	class BaseEngine {
		friend class ResourcePathHandler;
		friend class Engine;
	public:

		/**
		 * Default constructor.
		 */
		BaseEngine();

		/**
		 * Destructor.
		 */
		~BaseEngine();


		virtual void application(int argc, char *argv[],
		                        const std::string &name);
		
		
		virtual State *addState(State *newState);
		
		virtual void removeState(const std::string &name);
		
		void removeAllStates();
		
		virtual State *playState(const std::string &name);
		
		virtual State *getCurrentState();
		
		virtual State *getState(const std::string &name);
		


		virtual unsigned int getMinFps();
		
		virtual double getUpdatesPerSecond();
		
		virtual double getUpdateDelay();
		
		virtual void setMinFps(unsigned int newMinFps);
		
		virtual void setUpdatesPerSecond(double updatesPerSecond);
		
		virtual void pulse();
		
		virtual void initializeEngine(unsigned int resolutionWidth,
		                             unsigned int resolutionHeight,
		                             float contextWidth = 0.0f,
									  float contextHeight = 0.0f, WindowOrientation::type orientation = WindowOrientation::NORMAL);
		
		virtual double getSinceLastUpdate();
		
		virtual double getSinceLastRender();
		
		
		virtual bool isBufferSwapped();
		
		
		virtual void setBufferSwapped();
		
		virtual void exitApplication(int exitCode = 0);
		
		virtual void showMainWindow();
		
		virtual const std::string &getApplicationPath();
		
		virtual const std::string &getApplicationName();
		
		virtual int &getApplicationArgc();
		
		virtual char **getApplicationArgv();
		
		virtual MainWindow &getMainWindow();
		#ifdef BB_USE_STANDARD_RENDERER
		virtual GraphicDriver &getGraphicDriver();
		#endif
		virtual SoundEngine &getSoundEngine();
		
		virtual MusicEngine &getMusicEngine();

		/// Properly gets rid of a Singleton by its reference ID.
		virtual void destroySingleton(Singleton * toDelete);

		/// Registers a Singleton to the registry.
		/// This orders the Singletons to be deleted LIFO.
		virtual void registerSingleton(Singleton * singleton);

		/// Destroys singletons in the registry.
		/// This destroys from in LIFO order.
		virtual void destroyAllSingletons();

		// FIXME : Detail platforms needing this signal.
		/// Signal sent when the game needs to save some state before pausing on some platforms.
		sigly::Signal0<> saveState;

	protected:
		 void switchToNextState();

		
		/// A copy of argc
		int argc;
		
		/// A copy of argv
		char **argv;
		
		/// Map of states in the engine.
		std::map<std::string, State *> states;
		
		/// Pointer to the current state being played.
		State *currentState;
		
		/// Pointer to the next state.
		State *nextState;
		
		/// Time at which the last update was called on the current state.
		double lastUpdate;
		
		/// Time at which the last render was called on the current state.
		double lastRender;
		
		/// Internal update count between each render.
		unsigned int loops;
		
		/// Time at which the next update can be called.
		double nextUpdate;
		
		/// Delay between each update called on the current state.
		double updateDelay;
		
		/// Minimum renders that can be skipped between updates.
		unsigned int minFps;
		
		/// Flag to set when the buffer needs to be swapped.
		bool bufferSwapped;
		
		/// Flag to set when the application needs to exit.
		bool needsExit;
		
		/// Exit code to use when exiting the application
		int tmpExitCode;
		
		/**
		 * Flag used to limit rendering so it doesn't render more times than
		 * it updates.
		 */
		bool renderedSinceLastUpdate;
		
		/// Path to the current application binary.
		std::string applicationPath;
		
		/// Name of the application.
		std::string applicationName;

		/// Registry of all the Singletons, to later destroy them in (reverse) order.
		std::deque<Singleton * > singletons;

	};
}

#endif
