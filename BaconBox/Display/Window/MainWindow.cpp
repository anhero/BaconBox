#include "BaconBox/Display/Window/MainWindow.h"

#include "BaconBox/Core/Engine.h"
#include "BaconBox/Display/Driver/GraphicDriver.h"
#include "BaconBox/Input/Accelerometer/Accelerometer.h"
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
	
	Vector2 MainWindow::getResolution(){
		return Vector2(static_cast<float>(getResolutionWidth()), static_cast<float>(getResolutionHeight()));
	}
	Vector2 MainWindow::getContextSize(){
		return Vector2(getContextWidth(), getContextHeight());
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
	void MainWindow::setResolution(const Vector2 & res){
		setResolution(res.x, res.y);
	}

	void MainWindow::setResolution(unsigned int newResolutionWidth,
								   unsigned int newResolutionHeight) {
		resolutionWidth = (!orientationIsHorizontal() ? newResolutionWidth: newResolutionHeight);
		resolutionHeight = (orientationIsHorizontal() ? newResolutionWidth: newResolutionHeight);
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
			contextWidth = resolutionWidth;

		} else {
			contextWidth = (!orientationIsHorizontal() ? newContextWidth: newContextHeight);
		}

		if (newContextHeight == 0.0f) {
			contextHeight = resolutionHeight;

		} else {
			contextHeight = (orientationIsHorizontal() ? newContextWidth: newContextHeight);
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
	
	MainWindow::MainWindow() : sigly::HasSlots<sigly::SingleThreaded>(), inversedOrientationIncr(0), inversedOrientationTreshold(3), resolutionWidth(0), resolutionHeight(0),
	contextWidth(0), contextHeight(0), autoOrientation(WindowAutoOrientation::NONE), orientation(WindowOrientation::NORMAL) {
		Engine::onInitialize.connect(this, &MainWindow::onBaconBoxInit);
	}
	
	MainWindow::~MainWindow() {
	}
}
