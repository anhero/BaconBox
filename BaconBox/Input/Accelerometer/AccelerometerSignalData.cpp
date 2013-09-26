#include "BaconBox/Input/Accelerometer/AccelerometerSignalData.h"
#include <stddef.h>
using namespace BaconBox;

AccelerometerSignalData::AccelerometerSignalData(const AccelerometerState& newAccelerometerState) :
InputSignalData(), accelerometerState(newAccelerometerState),
x(this, &AccelerometerSignalData::getX, NULL),
y(this, &AccelerometerSignalData::getY, NULL),
z(this, &AccelerometerSignalData::getZ, NULL) {
}

AccelerometerSignalData::~AccelerometerSignalData() {
}


float AccelerometerSignalData::getX() const{
	return accelerometerState.getXAcceleration();
}
float AccelerometerSignalData::getY() const {
	return accelerometerState.getYAcceleration();

}
float AccelerometerSignalData::getZ() const{
	return accelerometerState.getZAcceleration();

}

