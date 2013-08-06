#include "BaconBox/Display/Window/MainWindow.h"

#include "BaconBox/Core/Engine.h"
#include "BaconBox/Display/Driver/GraphicDriver.h"

namespace BaconBox {
	const std::string MainWindow::DEFAULT_NAME = std::string("An unnamed BaconBox application");

	MainWindow &MainWindow::getInstance() {
		return Engine::getMainWindow();
	}

	void MainWindow::grabInput() {
		setInputGrabbed(true);
	}

	void MainWindow::releaseInput() {
		setInputGrabbed(false);
	}
    
    void MainWindow::showCursor(){
        
    }
    
    void MainWindow::hideCursor(){
        
    }
	
	
	unsigned int MainWindow::getResolutionWidth() {
		return (orientationIsHorizontal() ? resolutionHeight : resolutionWidth);
	}
	
	unsigned int MainWindow::getResolutionHeight() {
		return (!orientationIsHorizontal() ? resolutionHeight : resolutionWidth);
	}
	
	unsigned int MainWindow::getRealResolutionWidth(){
		return resolutionWidth;
	}
	
	unsigned int MainWindow::getRealResolutionHeight(){
		return resolutionHeight;
	}
	
	
	float MainWindow::getContextWidth() {
		return (orientationIsHorizontal() ? contextHeight : contextWidth);
	}
	
	float MainWindow::getContextHeight() {
		return (!orientationIsHorizontal() ? contextHeight : contextWidth);
	}
	
	float MainWindow::getRealContextWidth(){
		return contextWidth;
	}
	
	float MainWindow::getRealContextHeight(){
		return contextHeight;
	}

	void MainWindow::setResolution(unsigned int newResolutionWidth,
								   unsigned int newResolutionHeight) {
		resolutionWidth = (!orientationIsHorizontal() ? newResolutionWidth: newResolutionHeight);
		resolutionHeight = (orientationIsHorizontal() ? newResolutionWidth: newResolutionHeight);
	}
	bool MainWindow::orientationIsHorizontal(){
		return (this->getOrientation() == WindowOrientation::HORIZONTAL_LEFT || this->getOrientation() == WindowOrientation::HORIZONTAL_RIGHT);
	}
	
	void MainWindow::setContextSize(float newContextWidth, float newContextHeight) {
		
		if (newContextWidth == 0.0f) {
			contextWidth = resolutionWidth;

		} else {
			contextWidth = (!orientationIsHorizontal() ? newContextWidth: newContextHeight);
		}

		if (newContextHeight == 0.0f) {
			contextHeight = resolutionHeight;

		} else {
			contextHeight = (orientationIsHorizontal() ? newContextWidth: newContextHeight);
		}
	}
	
	WindowOrientation::type MainWindow::getOrientation() const {
		return orientation;
	}
	
	void MainWindow::setOrientation(WindowOrientation::type newOrientation) {
		if (orientation != newOrientation) {
			orientation = newOrientation;
		}
	}
	
	MainWindow::MainWindow() : sigly::HasSlots<sigly::SingleThreaded>(), resolutionWidth(0), resolutionHeight(0),
		contextWidth(0), contextHeight(0), orientation(WindowOrientation::NORMAL) {
		Engine::onInitialize.connect(this, &MainWindow::onBaconBoxInit);
	}
	
	MainWindow::~MainWindow() {
	}
}
