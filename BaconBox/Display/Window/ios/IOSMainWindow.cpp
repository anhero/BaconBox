#include "BaconBox/Display/Window/ios/IOSMainWindow.h"

#include "BaconBox/PlatformFlagger.h"

#include "BaconBox/Display/Driver/OpenGL/BBOpenGL.h"
#include "BaconBox/Core/Engine.h"
#include "BaconBox/Input/InputManager.h"
#include "BaconBox/Display/Window/ios/BaconBoxAppAppDelegate.h"
#import <UIKit/UIKit.h>
#include "BaconBox/Display/Driver/GraphicDriver.h"
#include "BaconBox/Console.h"
namespace BaconBox {
	
	void IOSMainWindow::onBaconBoxInit(unsigned int resolutionWidth,
									 unsigned int resolutionHeight,

									 float contextWidth, float contextHeight, WindowOrientation::type orientation) {
		
		

		
		CGRect screenBounds = [[UIScreen mainScreen] bounds];
		CGFloat screenScale = [[UIScreen mainScreen] scale];
		CGSize screenSize = CGSizeMake(screenBounds.size.width * screenScale, screenBounds.size.height * screenScale);


		viewController = [[BaconBoxAppViewController alloc] initWithFrame: screenBounds];
		[viewController setFrameInterval: 60.0f/Engine::getUpdatesPerSecond()];

		[BaconBoxAppAppDelegate setViewController: viewController];
		
		
		this->MainWindow::setResolution(screenSize.width, screenSize.height);
		setContextSize(contextWidth, contextHeight);
//		this->setOrientation(orientation);
		
		GraphicDriver::getInstance().resetProjection();

		
		InputManager::getInstance().setNbPointers(1);
		InputManager::getInstance().setNbKeyboards(1);
		InputManager::getInstance().setNbAccelerometers(1);
	}
//	WindowOrientation::type IOSMainWindow::getOrientation() const{
//		if(orientation == 0 || orientation == UIInterfaceOrientationPortrait){
//			return WindowOrientation::NORMAL;
//		}
//		else if(orientation == UIDeviceOrientationPortraitUpsideDown){
//			return WindowOrientation::UPSIDE_DOWN;
//		}
//		else if(orientation == UIInterfaceOrientationLandscapeLeft){
//			return WindowOrientation::HORIZONTAL_LEFT;
//		}
//		else if (orientation == UIInterfaceOrientationLandscapeRight){
//			return WindowOrientation::HORIZONTAL_RIGHT;
//		}
//	}
//	void IOSMainWindow::setOrientation(WindowOrientation::type newOrientation){}
	
	
	void IOSMainWindow::setContextSize(float newContextWidth, float newContextHeight) {
		float screenScale = 1/[[UIScreen mainScreen] scale];


		if (newContextWidth == 0.0f) {
			newContextWidth = context.x * screenScale;
			
		}
		if (newContextHeight == 0.0f) {
			newContextHeight = context.y * screenScale;
			
		}
		MainWindow::setContextSize(newContextWidth, newContextHeight);

	}
	
	void IOSMainWindow::setUpdatesPerSecond(double setFrameInterval){
		[viewController setFrameInterval: 60.0f/setFrameInterval];
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

