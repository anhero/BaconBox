#include "BaconBox/Audio/Flash/FlashAudio.h"

#include "BaconBox/Console.h"

#include "BaconBox/Helper/Flash/FlashHelper.h"

using namespace BaconBox;

void FlashAudio::play(int nbTimes) {
	//AS3::local::internal::trace(sound);
	//FlashHelper::callMethod(sound, "play", 0, args);
	Console::println("Stopping a FlashAudio object.");
}

void FlashAudio::stop() {
	Console::println("Stopping a FlashAudio object.");
}

void FlashAudio::pause() {
	Console::println("Pausing a FlashAudio object.");
}

void FlashAudio::resume() {
	Console::println("Resuming a FlashAudio object.");
}

bool FlashAudio::isLooping() {
	Console::println("Checking if a FlashAudio object is looping, returning false.");
	return false;
}

AudioState FlashAudio::getCurrentState() const {
	Console::println("Getting a FlashAudio object's audio state, returning STOPPED");
	return AudioState::STOPPED;
}

void FlashAudio::play(int nbTimes, double fadeIn) {
	Console::println("Playing a FlashAudio object " + Console::toString(nbTimes) + " times with a " +
			Console::toString(fadeIn) + " second(s) fade in.");
}

void FlashAudio::stop(double fadeOut) {
	Console::println("Stopping a FlashAudio object with a " + Console::toString(fadeOut) +
			" second(s) fade out.");
}

void FlashAudio::pause(double fadeOut) {
	Console::println("Pausing a FlashAudio object with a " + Console::toString(fadeOut) +
			" second(s) fade out.");
}

void FlashAudio::resume(double fadeIn) {
	Console::println("Resuming a FlashAudio object with a " + Console::toString(fadeIn) +
			" second(s) fade in.");
}

FlashAudio::~FlashAudio() {
	Console::println("Destroying a FlashAudio object.");
}

FlashAudio::FlashAudio() : BackgroundMusic(), SoundFX() {
	Console::println("Constructing a FlashAudio object.");
}
