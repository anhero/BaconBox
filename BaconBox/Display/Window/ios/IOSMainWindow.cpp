#include "BaconBox/Display/Window/ios/IOSMainWindow.h"

#include "BaconBox/PlatformFlagger.h"

#include "BaconBox/Display/Driver/OpenGL/BBOpenGL.h"
#include "BaconBox/Core/Engine.h"
#include "BaconBox/Input/InputManager.h"
#include "BaconBox/Display/Window/ios/BaconBoxAppAppDelegate.h"
#include "BaconBox/Display/Window/ios/BaconBoxAppViewController.h"
#import <UIKit/UIKit.h>

namespace BaconBox {
	
	void IOSMainWindow::onBaconBoxInit(unsigned int resolutionWidth,
									 unsigned int resolutionHeight,
									 float contextWidth, float contextHeight) {
		
		InputManager::getInstance().setNbPointers(1);
		InputManager::getInstance().setNbKeyboards(1);
		
		CGRect screenBounds = [[UIScreen mainScreen] bounds];
		this->MainWindow::setResolution(screenBounds.size.width, screenBounds.size.height);
		setContextSize(contextWidth, contextHeight);
		
		
		BaconBoxAppViewController *viewController = [[BaconBoxAppViewController alloc] initWithFrame: screenBounds];
		[BaconBoxAppAppDelegate setViewController: viewController];
		
	}
	
	IOSMainWindow::IOSMainWindow() : MainWindow() {
	}
	
	void IOSMainWindow::setCaption(const std::string &caption) {
	}
	
	bool IOSMainWindow::isFullScreen() const {
		return true;
	}
	
	void IOSMainWindow::setFullScreen(bool) {
	}
	
	bool IOSMainWindow::isInputGrabbed() const {
		return true;
	}
	
	void IOSMainWindow::setInputGrabbed(bool newInputGrabbed) {
	}
	
	void IOSMainWindow::show() {
		//Need the next to lines of code to prevent the dead code strip
		//from striping the BaconBoxAppDelegate Class
		BaconBoxAppAppDelegate *appDelegate = [BaconBoxAppAppDelegate alloc];
		
		UIApplicationMain(Engine::getApplicationArgc(), Engine::getApplicationArgv(), nil, @"BaconBoxAppAppDelegate");
	}
	
	IOSMainWindow::~IOSMainWindow() {
	}
	
	void IOSMainWindow::setResolution(unsigned int resolutionWidth,
	                                  unsigned int resolutionHeight) {
	}
}

