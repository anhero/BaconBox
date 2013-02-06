#include "BaconBox/Audio/Flash/FlashSoundFX.h"

#include "BaconBox/Console.h"

#include "BaconBox/Helper/Flash/FlashHelper.h"

using namespace BaconBox;

void FlashSoundFX::play(int nbTimes) {
	FlashHelper::callMethod(sound, "play", 0, NULL);
}

void FlashSoundFX::stop() {
	Console::println("Stopping a FlashSoundFX object.");
}

void FlashSoundFX::pause() {
	Console::println("Pausing a FlashSoundFX object.");
}


void FlashSoundFX::resume() {
	Console::println("Resuming a FlashSoundFX object.");
}

bool FlashSoundFX::isLooping() {
	Console::println("Checking if a FlashSoundFX object is looping, returning false.");
	return false;
}

AudioState FlashSoundFX::getCurrentState() const {
	Console::println("Getting a FlashSoundFX object's audio state, returning STOPPED");
	return AudioState::STOPPED;
}

void FlashSoundFX::play(int nbTimes, double fadeIn) {
	Console::println("Playing a FlashSoundFX object " + Console::toString(nbTimes) + " times with a " +
			Console::toString(fadeIn) + " second(s) fade in.");
}

void FlashSoundFX::stop(double fadeOut) {
	Console::println("Stopping a FlashSoundFX object with a " + Console::toString(fadeOut) +
			" second(s) fade out.");
}

void FlashSoundFX::pause(double fadeOut) {
	Console::println("Pausing a FlashSoundFX object with a " + Console::toString(fadeOut) +
			" second(s) fade out.");
}

void FlashSoundFX::resume(double fadeIn) {
	Console::println("Resuming a FlashSoundFX object with a " + Console::toString(fadeIn) +
			" second(s) fade in.");
}

FlashSoundFX::~FlashSoundFX() {
	Console::println("Destroying a FlashSoundFX object.");
}

FlashSoundFX::FlashSoundFX() :SoundFX() {
	Console::println("Constructing a FlashSoundFX object.");
}
