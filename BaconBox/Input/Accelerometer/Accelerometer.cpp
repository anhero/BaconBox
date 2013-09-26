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

bool Accelerometer::isActive() const {
	return active;
}

Accelerometer::Accelerometer() : InputDevice() {
}

Accelerometer::~Accelerometer() {
}

void Accelerometer::updateDevice() {
	InputDevice::updateDevice();
}

const AccelerometerState& Accelerometer::getState() const {
	return state;
}


void Accelerometer::setState(float xAcceleration, float yAcceleration, float zAcceleration){
	state.xAcceleration = xAcceleration;
	state.yAcceleration = yAcceleration;
	state.zAcceleration = zAcceleration;

}
