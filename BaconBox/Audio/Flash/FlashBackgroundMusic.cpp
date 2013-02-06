#include "BaconBox/Audio/Flash/FlashBackgroundMusic.h"

#include "BaconBox/Console.h"

#include "BaconBox/Helper/Flash/FlashHelper.h"

using namespace BaconBox;

void FlashBackgroundMusic::play(int nbTimes) {
	FlashHelper::callMethod(sound, "play", 0, NULL);
}

void FlashBackgroundMusic::stop() {
	Console::println("Stopping a FlashBackgroundMusic object.");
}

void FlashBackgroundMusic::pause() {
	Console::println("Pausing a FlashBackgroundMusic object.");
}


void FlashBackgroundMusic::resume() {
	Console::println("Resuming a FlashBackgroundMusic object.");
}

bool FlashBackgroundMusic::isLooping() {
	Console::println("Checking if a FlashBackgroundMusic object is looping, returning false.");
	return false;
}

AudioState FlashBackgroundMusic::getCurrentState() const {
	Console::println("Getting a FlashBackgroundMusic object's audio state, returning STOPPED");
	return AudioState::STOPPED;
}

void FlashBackgroundMusic::play(int nbTimes, double fadeIn) {
	Console::println("Playing a FlashBackgroundMusic object " + Console::toString(nbTimes) + " times with a " +
			Console::toString(fadeIn) + " second(s) fade in.");
}

void FlashBackgroundMusic::stop(double fadeOut) {
	Console::println("Stopping a FlashBackgroundMusic object with a " + Console::toString(fadeOut) +
			" second(s) fade out.");
}

void FlashBackgroundMusic::pause(double fadeOut) {
	Console::println("Pausing a FlashBackgroundMusic object with a " + Console::toString(fadeOut) +
			" second(s) fade out.");
}

void FlashBackgroundMusic::resume(double fadeIn) {
	Console::println("Resuming a FlashBackgroundMusic object with a " + Console::toString(fadeIn) +
			" second(s) fade in.");
}

FlashBackgroundMusic::~FlashBackgroundMusic() {
	Console::println("Destroying a FlashBackgroundMusic object.");
}

FlashBackgroundMusic::FlashBackgroundMusic() : BackgroundMusic() {
	Console::println("Constructing a FlashBackgroundMusic object.");
}
