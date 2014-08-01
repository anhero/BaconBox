/**
 * @file
 * @ingroup StateMachine
 */

#ifndef BB_ENGINE_H
#define BB_ENGINE_H

#include <map>
#include <string>
#include <sigly.h>
#include "BaconBox/PlatformFlagger.h"

#include "BaconBox/Core/State.h"
#include "BaconBox/Display/Window/WindowOrientation.h"

#include BB_ENGINE_INCLUDE

namespace BaconBox {
	class MainWindow;
	class GraphicDriver;
	class SoundEngine;
	class MusicEngine;
	/**
	 * Class managing the states.
	 * @ingroup StateMachine
	 */
	class Engine {
		friend class ResourcePathHandler;
	public:
		
		static const double DEFAULT_UPDATES_PER_SECOND;
		static const unsigned int DEFAULT_MIN_FRAMES_PER_SECOND = 5;
		
		static const std::string DEFAULT_APPLICATION_NAME;
		
		/**
		 * This function must be called by the main function. The main function
		 * arguments must be passed this function along with the desired
		 * application name.
		 * @param argc Main's received argc.
		 * @param argv Main's received argv.
		 * @param name Application's name (your game's title for example). Set
		 * to "BaconBoxApp" by default.
		 */
		static void application(int argc, char *argv[],
		                        const std::string &name = DEFAULT_APPLICATION_NAME);
		
		
		
		static sigly::Signal0<> update;
		
		/// Signal sent when the BaconBox engine is initialized.
		static sigly::Signal5<unsigned int, unsigned int, float, float, WindowOrientation::type> onInitialize;
		
		/**
		 * Adds a state to the engine's list.
		 * @param newState Pointer to the state to add to the engine.
		 * @return Pointer to the added state. The same as the one received.
		 */
		static State *addState(State *newState);
		
	#ifdef BB_LUA
		static State * addState(lua_State * L);
	#endif //BB_LUA
		
		
		static State *getState(const std::string &name);
		
	
		/**
		 * Removes a state from the engine.
		 * @param name Name of the state to remove from the engine.
		 */
		static void removeState(const std::string &name);
		
		static void removeAllStates();
		
		/**
		 * Changes the current state to the one asked for.
		 * @param name Name of the state to become the current one.
		 * @return Pointer to the state starting to be played.
		 */
		static State *playState(const std::string &name);
		
		/**
		 * Gets the current state being played.
		 * @return Pointer to the state being played.
		 */
		static State *getCurrentState();
		
		/**
		 * Gets the minimum fps.
		 * @return Minimum fps.
		 */
		static unsigned int getMinFps();
		
		/**
		 * Gets the number of updates per second.
		 * @return Number of updates per second.
		 */
		static double getUpdatesPerSecond();
		
		/**
		 * Return the normal delay between each update (1/Update per second)
		 */
		static double getUpdateDelay();
		
		/**
		 * Sets the minimum number of frames per second to be rendered. Cannot
		 * have a higher number than the number of updates per second.
		 * @param newMinFps Minimum number of frames per second.
		 */
		static void setMinFps(unsigned int newMinFps);
		
		/**
		 * Sets the updates per second. Updates per second called on the current
		 * state. Cannot have a lower number than the number of frames per
		 * second.
		 * @param updatesPerSecond Number of updates per second.
		 */
		static void setUpdatesPerSecond(double updatesPerSecond);
		
		/**
		 * Called by the context to call the update and the render correctly
		 * on the current state.
		 */
		static void pulse();
		
		/**
		 * Initialize the different parts of the engine (drawer, audio engine, etc.)
		 * @param resolutionWidth Set the window resolution width
		 * @param resolutionHeight Set the window resolution height
		 * @param contextWidth Define the number of arbitrary units from
		 * one side of the window to another (set it to 0 if you wan't to work in pixel).
		 * @param contextHeight Define the number of arbitrary units from
		 * the top of the window to the bottom (set it to 0 if you wan't to work in pixel).
		 */
		static void initializeEngine(unsigned int resolutionWidth,
		                             unsigned int resolutionHeight,
		                             float contextWidth = 0.0f,
		                             float contextHeight = 0.0f, WindowOrientation::type orientation = WindowOrientation::NORMAL);
		
		/**
		 * Gets the time elapsed since the last update called on a state.
		 * @return Time in seconds since the last update called on a state.
		 */
		static double getSinceLastUpdate();
		
		/**
		 * Gets the time elapsed since the last render called on a state.
		 * @return Time in seconds since the last render called on a state.
		 */
		static double getSinceLastRender();
		
		
		/**
		 * Checks if the buffer was swapped since the last update.
		 */
		static bool isBufferSwapped();
		
		
		/**
		 * Tells the engine the buffer was swapped.
		 */
		static void setBufferSwapped();
		
		/**
		 * Calls the standard C exit function at the end of the pulse.
		 * @param exitCode Exit code to pass to the standard exit function.
		 */
		static void exitApplication(int exitCode = 0);
		
		/**
		 * Shows the window and starts the application.
		 */
		static void showMainWindow();
		
		/**
		 * Gets the application's path in the filesystem.
		 * @return String containing the application's path in the filesystem.
		 * @see BaconBox::Engine::applicationPath
		 */
		static const std::string &getApplicationPath();
		
		/**
		 * Gets the application's name.
		 * @return String containing the application/game's name.
		 * @see BaconBox::Engine::applicationName
		 */
		static const std::string &getApplicationName();
		
		/**
		 * Gets the application's argument count, generally as passed to main.
		 */
		static int &getApplicationArgc();
		
		/**
		 * Gets the application's argument values, generally as passed to main.
		 */
		static char **getApplicationArgv();
		
		/**
		 * Gets the main window.
		 * @return Reference to the main window.
		 */
		static MainWindow &getMainWindow();
		
		/**
		 * Gets the graphic driver.
		 * @return Reference to the graphic driver.
		 */
		static GraphicDriver &getGraphicDriver();
		
		/**
		 * Gets the sound engine.
		 * @return Reference to the sound engine.
		 */
		static SoundEngine &getSoundEngine();
		
		/**
		 * Gets the music engine.
		 * @return Reference to the music engine.
		 */
		static MusicEngine &getMusicEngine();
		
		/**
		 * Gets the engine singleton instance.
		 * @return Reference to the engine's singleton.
		 */
		static BB_ENGINE_IMPL &getInstance();
		

		/**
		 * Raises the debugger on supported platforms.
		 */
		static void raiseDebugger();

	private:
		

		
	};
}

#endif
