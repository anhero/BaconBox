#include "BaconBox/Display/Window/NullMainWindow.h"

#include "BaconBox/Input/InputManager.h"
namespace BaconBox {

	void NullMainWindow::onBaconBoxInit(unsigned int resolutionWidth, unsigned int resolutionHeight, float contextWidth, float contextHeight) {
		this->MainWindow::setResolution(resolutionWidth, resolutionHeight);
		this->MainWindow::setContextSize(contextWidth, contextHeight);

		
		InputManager::getInstance().setNbKeyboards(1);
		InputManager::getInstance().setNbPointers(1);

	}

	void NullMainWindow::show() {
		
	}

	void NullMainWindow::setResolution(unsigned int resolutionWidth,
	                                  unsigned int resolutionHeight) {
		this->MainWindow::setResolution(resolutionWidth, resolutionHeight);
//		GraphicDriver::getInstance().initializeGraphicDriver();
	}

	void NullMainWindow::setContextSize(float newContextWidth,
	                                   float newContextHeight) {
		this->MainWindow::setContextSize(newContextWidth, newContextHeight);
//		GraphicDriver::getInstance().initializeGraphicDriver();
	}

	void NullMainWindow::setCaption(const std::string &caption) {
	}

	bool NullMainWindow::isFullScreen() const {
		return false;
	}

	void NullMainWindow::setFullScreen(bool newFullScreen) {
	}

	bool NullMainWindow::isInputGrabbed() const {
		return false;
	}

	void NullMainWindow::setInputGrabbed(bool newInputGrabbed) {
	}

	NullMainWindow::NullMainWindow() : MainWindow(){

	}

	NullMainWindow::~NullMainWindow() {
		
	}
    
    void NullMainWindow::hideCursor(){

    }
    
    void NullMainWindow::showCursor(){

    }
}
