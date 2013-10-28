#include "BaconBox/Input/Accelerometer/AccelerometerState.h"

using namespace BaconBox;
using namespace VMATH_NAMESPACE;
const float AccelerometerState::STARTING_ACCELERATION = 0.0f;

AccelerometerState::AccelerometerState() : InputState(), acceleration(STARTING_ACCELERATION, STARTING_ACCELERATION, STARTING_ACCELERATION) {
}

AccelerometerState::~AccelerometerState() {
}

float AccelerometerState::getXAcceleration() const {
	return acceleration.x;
}

float AccelerometerState::getYAcceleration() const {
	return acceleration.y;
}

float AccelerometerState::getZAcceleration() const {
	return acceleration.z;
}


const Vector3f & AccelerometerState::getAcceleration() const{
	return acceleration;
}