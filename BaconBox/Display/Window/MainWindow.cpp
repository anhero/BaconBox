#include "BaconBox/PlatformFlagger.h"
#include "BaconBox/Display/Window/MainWindow.h"

#include "BaconBox/Core/Engine.h"
#include "BaconBox/Display/Driver/GraphicDriver.h"
#include "BaconBox/Input/Accelerometer/Accelerometer.h"
#include "BaconBox/Console.h"

#include BB_MAIN_WINDOW_INCLUDE

namespace BaconBox {
	const std::string MainWindow::DEFAULT_NAME = std::string("An unnamed BaconBox application");

	MainWindow &MainWindow::getInstance() {
		return * static_cast<MainWindow *>(BB_MAIN_WINDOW_IMPL);
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
	const Vector2 & MainWindow::getRealResolution(){
		return resolution;
	}

	Vector2 MainWindow::getResolution(){
		if (orientationIsHorizontal()) {
			return Vector2(resolution.y, resolution.x);
		}
		else{
			return resolution;
		}
	}
	Vector2 MainWindow::getContextSize(){
		if (orientationIsHorizontal()) {
			return Vector2(context.y, context.x);
		}
		else{
			return context;
		}
	}
	
	const Vector2 & MainWindow::getRealContextSize(){
		return context;
	}
	
	unsigned int MainWindow::getResolutionWidth() {
		return getResolution().x;
	}
	
	unsigned int MainWindow::getResolutionHeight() {
		return getResolution().y;
	}
	
	unsigned int MainWindow::getRealResolutionWidth(){
		return getRealResolution().x;
	}
	
	unsigned int MainWindow::getRealResolutionHeight(){
		return getRealResolution().y;
	}
	
	
	float MainWindow::getContextWidth() {
		return getContextSize().x;
	}
	
	float MainWindow::getContextHeight() {
		return getContextSize().y;
	}
	
	float MainWindow::getRealContextWidth(){
		return getRealContextSize().x;
	}
	
	float MainWindow::getRealContextHeight(){
		return getRealContextSize().y;
	}
	void MainWindow::setResolution(const Vector2 & res){
		setResolution(res.x, res.y);
	}

	void MainWindow::setResolution(unsigned int newResolutionWidth,
								   unsigned int newResolutionHeight) {
		resolution.x = (!orientationIsHorizontal() ? newResolutionWidth: newResolutionHeight);
		resolution.y = (orientationIsHorizontal() ? newResolutionWidth: newResolutionHeight);
		GraphicDriver::getInstance().resetProjection();
	}
	bool MainWindow::orientationIsHorizontal(){
		return (this->getOrientation() == WindowOrientation::HORIZONTAL_LEFT || this->getOrientation() == WindowOrientation::HORIZONTAL_RIGHT);
	}
	
	void MainWindow::setContextSize(Vector2 size){
		setContextSize(size.x, size.y);
	}
	
	void MainWindow::setContextSize(float newContextWidth, float newContextHeight) {
		if (newContextWidth == 0.0f) {
			context.x = resolution.x;

		} else {
			context.x = (!orientationIsHorizontal() ? newContextWidth: newContextHeight);
		}

		if (newContextHeight == 0.0f) {
			context.y = resolution.y;

		} else {
			context.y = (orientationIsHorizontal() ? newContextWidth: newContextHeight);
		}

		GraphicDriver::getInstance().resetProjection();
	}
	
	WindowOrientation::type MainWindow::getOrientation() const {
		return orientation;
	}
	
	void MainWindow::accelChange(AccelerometerSignalData data){
		if (autoOrientation = WindowAutoOrientation::LANDSCAPE) {
		if (orientation == WindowOrientation::HORIZONTAL_LEFT) {
			if(data.getX() < 0){
				inversedOrientationIncr++;
			}
			else{
				inversedOrientationIncr = 0;
			}
			if (inversedOrientationIncr > inversedOrientationTreshold) {
				inversedOrientationIncr = 0;
				setOrientation(WindowOrientation::HORIZONTAL_RIGHT);
			}
		}
		else if (orientation == WindowOrientation::HORIZONTAL_RIGHT) {
			if(data.getX() > 0){
				inversedOrientationIncr++;
			}
			else{
				inversedOrientationIncr = 0;
			}
			if (inversedOrientationIncr > inversedOrientationTreshold) {
				inversedOrientationIncr = 0;
				setOrientation(WindowOrientation::HORIZONTAL_LEFT);
			}
		}
		}
	}

	
	void MainWindow::setAutoOrientation(WindowAutoOrientation::type autoOrientation){
		Accelerometer * accel = Accelerometer::getDefault();
		if(accel){
			accel->activate();
			accel->activateSignals();
			accel->change.disconnect(this);
			if (autoOrientation != WindowAutoOrientation::NONE) {
				accel->change.connect(this, &MainWindow::accelChange);
			}
		}
		this->autoOrientation = autoOrientation;
		
	}

	void MainWindow::setOrientation(WindowOrientation::type newOrientation) {
		orientationChanged.shoot(newOrientation);
		bool wasHoriz = orientationIsHorizontal();
		if (orientation != newOrientation) {
			orientation = newOrientation;
		}
		if(orientationIsHorizontal() != wasHoriz) {
			setResolution(this->getResolutionHeight(), this->getResolutionWidth());
			setContextSize(this->getContextHeight(), this->getContextWidth());
		}
		else{
			setResolution(this->getResolutionWidth(), this->getResolutionHeight());
			setContextSize(this->getContextWidth(), this->getContextHeight());
		}
		
		}
	
	MainWindow::MainWindow() : sigly::HasSlots<SIGLY_DEFAULT_MT_POLICY>(), inversedOrientationIncr(0), inversedOrientationTreshold(3), resolution(), context(), autoOrientation(WindowAutoOrientation::NONE), orientation(WindowOrientation::NORMAL) {
		Engine::onInitialize.connect(this, &MainWindow::onBaconBoxInit);
	}
	
	MainWindow::~MainWindow() {
	}
}
