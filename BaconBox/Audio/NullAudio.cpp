#include "BaconBox/Audio/NullAudio.h"

#include "BaconBox/Console.h"

using namespace BaconBox;

void NullAudio::play(int nbTimes) {
	Console::println("Playing a NullAudio object " + Console::toString(nbTimes) + " times.");
	this->nbTimes = nbTimes;
	if(nbTimes == -1){
		state = AudioState::PLAYING;
	}
	else{
		state = AudioState::STOPPED;
	}
}

void NullAudio::stop() {
	Console::println("Stopping a NullAudio object.");
	state = AudioState::STOPPED;

}

void NullAudio::pause() {
	Console::println("Pausing a NullAudio object.");
	state = AudioState::PAUSED;

}

void NullAudio::resume() {
	Console::println("Resuming a NullAudio object.");
	if(nbTimes == -1){
		state = AudioState::PLAYING;
	}
	else{
		state = AudioState::STOPPED;
	}
}

bool NullAudio::isLooping() {
	return nbTimes == -1;
}

AudioState::type NullAudio::getCurrentState() const {
	return state;
}

void NullAudio::play(int nbTimes, double fadeIn) {
	Console::println("Playing a NullAudio object " + Console::toString(nbTimes) + " times with a " +
			Console::toString(fadeIn) + " second(s) fade in.");
	if(nbTimes == -1){
		state = AudioState::PLAYING;
	}
	else{
		state = AudioState::STOPPED;
	}
}

void NullAudio::stop(double fadeOut) {
	Console::println("Stopping a NullAudio object with a " + Console::toString(fadeOut) +
			" second(s) fade out.");
	state = AudioState::STOPPED;
}

void NullAudio::pause(double fadeOut) {
	Console::println("Pausing a NullAudio object with a " + Console::toString(fadeOut) +
			" second(s) fade out.");
	state = AudioState::PAUSED;
}

void NullAudio::resume(double fadeIn) {
	Console::println("Resuming a NullAudio object with a " + Console::toString(fadeIn) +
			" second(s) fade in.");
	if(nbTimes == -1){
		state = AudioState::PLAYING;
	}
	else{
		state = AudioState::STOPPED;
	}
}

NullAudio::~NullAudio() {
	Console::println("Destroying a NullAudio object.");
}

NullAudio::NullAudio() : BackgroundMusic(), SoundFX() {
	Console::println("Constructing a NullAudio object.");
}
