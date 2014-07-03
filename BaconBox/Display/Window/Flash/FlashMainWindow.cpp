#include "BaconBox/Display/Window/Flash/FlashMainWindow.h"

#include "BaconBox/Input/InputManager.h"
namespace BaconBox {


	void FlashMainWindow::onBaconBoxInit(unsigned int resolutionWidth, unsigned int resolutionHeight, float contextWidth, float contextHeight, BaconBox::WindowOrientation::type) {
		this->MainWindow::setResolution(resolutionWidth, resolutionHeight);
		this->MainWindow::setContextSize(contextWidth, contextHeight);

		InputManager::getInstance().setNbKeyboards(1);
		InputManager::getInstance().setNbPointers(1);

	}

	void FlashMainWindow::show() {
		
	}

	void FlashMainWindow::setResolution(unsigned int resolutionWidth,
	                                  unsigned int resolutionHeight) {
		this->MainWindow::setResolution(resolutionWidth, resolutionHeight);
//		GraphicDriver::getInstance().initializeGraphicDriver();
	}

	void FlashMainWindow::setContextSize(float newContextWidth,
	                                   float newContextHeight) {
		this->MainWindow::setContextSize(newContextWidth, newContextHeight);
//		GraphicDriver::getInstance().initializeGraphicDriver();
	}

	void FlashMainWindow::setUpdatesPerSecond(double){

	}

	void FlashMainWindow::setCaption(const std::string &caption) {
	}

	bool FlashMainWindow::isFullScreen() const {
	}

	void FlashMainWindow::setFullScreen(bool newFullScreen) {
	}

	bool FlashMainWindow::isInputGrabbed() const {
	}

	void FlashMainWindow::setInputGrabbed(bool newInputGrabbed) {
	}

	FlashMainWindow::FlashMainWindow() : MainWindow(){

	}

	FlashMainWindow::~FlashMainWindow() {
		
	}
    
    void FlashMainWindow::hideCursor(){

    }
    
    void FlashMainWindow::showCursor(){

    }
}
