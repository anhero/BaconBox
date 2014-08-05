#include "BaconBox/Core/Engine.h"


#ifdef BB_LUA
#include "BaconBox/Helper/Lua/LuaHelper.h"
#endif //BB_LUA

#ifdef BB_LINUX
#include <signal.h>
#endif

namespace BaconBox {

	BaseEngine * Engine::instance = NULL;
	const double Engine::DEFAULT_UPDATES_PER_SECOND = 60.0;
	const std::string Engine::DEFAULT_APPLICATION_NAME = std::string("BaconBoxApp");
	sigly::Signal5<unsigned int, unsigned int, float, float, WindowOrientation::type> Engine::onInitialize = sigly::Signal5<unsigned int, unsigned int, float, float, WindowOrientation::type>();
	sigly::Signal0<> Engine::update = sigly::Signal0<>();

	void Engine::application(int argc, char *argv[], const std::string &name) {
		getInstance().application(argc,argv,name);
	}
	
	State *Engine::addState(State *newState) {
		return getInstance().addState(newState);
	}
	
#ifdef BB_LUA
	State * Engine::addState(lua_State * L){
		return Engine::addState(reinterpret_cast<State*>(LuaHelper::getEntityFromLuaEntity(L)));
	}
#endif //BB_LUA
	
	void Engine::removeState(const std::string &name) {
		getInstance().removeState(name);
	}
	
	void Engine::removeAllStates() {
		getInstance().removeAllStates();
	}
	
	State *Engine::playState(const std::string &name) {
		return getInstance().playState(name);
	}
	
	
	State *Engine::getState(const std::string &name){
		return getInstance().getState(name);
	}
	
	State *Engine::getCurrentState() {
		return getInstance().getCurrentState();
	}
	
	unsigned int Engine::getMinFps() {
		return getInstance().getMinFps();
	}
	
	double Engine::getUpdatesPerSecond() {
		return getInstance().getUpdatesPerSecond();
	}
	
	double Engine::getUpdateDelay() {
		return getInstance().getUpdateDelay();
	}
	
	void Engine::setMinFps(unsigned int newMinFps) {
		getInstance().setMinFps(newMinFps);
	}
	
	
	void Engine::setUpdatesPerSecond(double updatesPerSecond) {
		getInstance().setUpdatesPerSecond(updatesPerSecond);
	}
	
	void Engine::pulse() {
		Engine::update();
		getInstance().pulse();
	}
	
	void Engine::initializeEngine(unsigned int resolutionWidth,
	                              unsigned int resolutionHeight,
	                              float contextWidth,
	                              float contextHeight, WindowOrientation::type orientation) {
		getInstance().initializeEngine(resolutionWidth, resolutionHeight, contextWidth, contextHeight, orientation);
	}
	
	double Engine::getSinceLastUpdate() {
		return getInstance().getSinceLastUpdate();
	}
	
	double Engine::getSinceLastRender() {
		return getInstance().getSinceLastRender();
	}
	
	bool Engine::isBufferSwapped() {
		return getInstance().isBufferSwapped();
	}
	
	void Engine::setBufferSwapped() {
		getInstance().setBufferSwapped();
	}
	
	void Engine::exitApplication(int exitCode) {
		getInstance().exitApplication(exitCode);
	}
	
	void Engine::showMainWindow() {
		getInstance().showMainWindow();
	}
	
	const std::string &Engine::getApplicationPath() {
		return getInstance().getApplicationPath();
	}
	
	const std::string &Engine::getApplicationName() {
		return getInstance().getApplicationName();
	}
	
	int &Engine::getApplicationArgc() {
		return getInstance().getApplicationArgc();
	}
	
	char **Engine::getApplicationArgv() {
		return getInstance().getApplicationArgv();
	}
	
	MainWindow &Engine::getMainWindow() {
		return getInstance().getMainWindow();
	}
	
	GraphicDriver &Engine::getGraphicDriver() {
		return getInstance().getGraphicDriver();
	}
	
	SoundEngine &Engine::getSoundEngine() {
		return getInstance().getSoundEngine();
	}
	
	MusicEngine &Engine::getMusicEngine() {
		return getInstance().getMusicEngine();
	}
	
	void Engine::raiseDebugger() {
#if defined(BB_DEBUG)
#if defined(BB_LINUX)
		raise(SIGINT);
#endif
#endif
	}


	void Engine::setInstance(BaseEngine &instance) {
		Engine::instance = &instance;
	}

	BaseEngine &Engine::getInstance() {
		if (instance == NULL) {
			PRLN("BaconBox::Engine needs to be initialized before being used.");
			// Give a chance to debug.
			Engine::raiseDebugger();
			// Then abort.
			abort();
		}
		return * instance;
	}
	
}
