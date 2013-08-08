#include "BaconBox/Display/Window/ios/IOSMainWindow.h"

#include "BaconBox/PlatformFlagger.h"

#include "BaconBox/Display/Driver/OpenGL/BBOpenGL.h"
#include "BaconBox/Core/Engine.h"
#include "BaconBox/Input/InputManager.h"
#include "BaconBox/Display/Window/ios/BaconBoxAppAppDelegate.h"

#import <UIKit/UIKit.h>

namespace BaconBox {
	
	void IOSMainWindow::onBaconBoxInit(unsigned int resolutionWidth,
									 unsigned int resolutionHeight,
									 float contextWidth, float contextHeight, WindowOrientation::type orientation) {
				NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

		
		InputManager::getInstance().setNbPointers(1);
		InputManager::getInstance().setNbKeyboards(1);
		CGRect screenBounds = [[UIScreen mainScreen] bounds];
		CGFloat screenScale = [[UIScreen mainScreen] scale];
		CGSize screenSize = CGSizeMake(screenBounds.size.width * screenScale, screenBounds.size.height * screenScale);
		
		this->MainWindow::setResolution(screenSize.width, screenSize.height);
		this->setOrientation(orientation);
		
		setContextSize(contextWidth, contextHeight);

		BaconBoxAppViewController *viewController = [[BaconBoxAppViewController alloc] initWithFrame: screenBounds];
		[BaconBoxAppAppDelegate setViewController: viewController];
		[pool release];
		
	}
	
	
	void IOSMainWindow::setContextSize(float newContextWidth, float newContextHeight) {
		float screenScale = 1/[[UIScreen mainScreen] scale];


		if (newContextWidth == 0.0f) {
			contextWidth = resolutionWidth * screenScale;
			
		} else {
			contextWidth = newContextWidth;
		}
		
		if (newContextHeight == 0.0f) {
			contextHeight = resolutionHeight * screenScale;
			
		} else {
			contextHeight = newContextHeight;
		}
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
		NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
		//Need the next to lines of code to prevent the dead code strip
		//from striping the BaconBoxAppDelegate Class
		BaconBoxAppAppDelegate *appDelegate = [BaconBoxAppAppDelegate alloc];
		[appDelegate release];
		
		UIApplicationMain(Engine::getApplicationArgc(), Engine::getApplicationArgv(), nil, @"BaconBoxAppAppDelegate");
		[pool release];
	}
	
	IOSMainWindow::~IOSMainWindow() {
	}
	
	void IOSMainWindow::setResolution(unsigned int resolutionWidth,
	                                  unsigned int resolutionHeight) {
	}
}

