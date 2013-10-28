#include "BaconBox/Input/Accelerometer/Accelerometer.h"

#include "BaconBox/Input/InputManager.h"

using namespace BaconBox;

Accelerometer* Accelerometer::getDefault() {
	return InputManager::getDefaultAccelerometer();
}

void Accelerometer::activateSignals() {
	signalsActive = true;
}

void Accelerometer::deactivateSignals() {
	signalsActive = false;
}

bool Accelerometer::areSignalsActive() const {
	return signalsActive;
}

void Accelerometer::activate() {
	active = true;
}

void Accelerometer::deactivate() {
	active = false;
}
void Accelerometer::calibrateFromSelf(){
	calibrateFromVector(state.getAcceleration());
}
void Accelerometer::calibrateFromVector(const VMATH_NAMESPACE::Vector3f &vec){
	VMATH_NAMESPACE::Vector3f normalized = vec;
	normalized.normalize();
	VMATH_NAMESPACE::Quatf rotateQuat = VMATH_NAMESPACE::Quatf::FromToRotation(VMATH_NAMESPACE::Vector3f(0.0,0.0,-1.0), normalized);
	rotateQuat.normalize();
	VMATH_NAMESPACE::Matrix4f mat = rotateQuat.transform();
	calibrationMatrix = mat.inverse();
}



const vmath::Matrix4f & Accelerometer::getCalibrationMatrix(){
	return this->calibrationMatrix;
}

void Accelerometer::setCalibrationMatrix(const vmath::Matrix4f & calibrationMatrix){
	this->calibrationMatrix = calibrationMatrix;
}

bool Accelerometer::isActive() const {
	return active;
}

Accelerometer::Accelerometer() : InputDevice(), calibrationMatrix() {
}

Accelerometer::~Accelerometer() {
}

void Accelerometer::updateDevice() {
	InputDevice::updateDevice();
}

const AccelerometerState& Accelerometer::getState() const {
	return state;
}

const VMATH_NAMESPACE::Vector3f & Accelerometer::getAcceleration(){
	return state.getAcceleration();
}

const VMATH_NAMESPACE::Vector3f Accelerometer::getCalibratedAcceleration(){
	return calibrationMatrix * getAcceleration();
}


void Accelerometer::setState(float xAcceleration, float yAcceleration, float zAcceleration){
	state.acceleration.x = xAcceleration;
	state.acceleration.y = yAcceleration;
	state.acceleration.z = zAcceleration;

}
