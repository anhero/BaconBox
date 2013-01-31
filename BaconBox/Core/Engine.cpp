#include "BaconBox/Core/Engine.h"

namespace BaconBox {
	const double Engine::DEFAULT_UPDATES_PER_SECOND = 60.0;
	const std::string Engine::DEFAULT_APPLICATION_NAME = std::string("BaconBoxApp");
	sigly::Signal4<unsigned int, unsigned int, float, float> Engine::onInitialize = sigly::Signal4<unsigned int, unsigned int, float, float>();
	

	void Engine::application(int argc, char *argv[], const std::string &name) {
		getInstance().application(argc,argv,name);
	}
	
	State *Engine::addState(State *newState) {
		return getInstance().addState(newState);
	}
	
	void Engine::removeState(const std::string &name) {
		getInstance().removeState(name);
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
		getInstance().pulse();
	}
	
	void Engine::initializeEngine(unsigned int resolutionWidth,
	                              unsigned int resolutionHeight,
	                              float contextWidth,
	                              float contextHeight) {
		getInstance().initializeEngine(resolutionWidth, resolutionHeight, contextWidth, contextHeight);
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
	
	BB_ENGINE_IMPL &Engine::getInstance() {
		static BB_ENGINE_IMPL instance;
		return instance;
	}
	
}
