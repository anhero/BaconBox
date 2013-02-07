#include "BaconBox/Audio/Flash/FlashAudio.h"

#include "BaconBox/Console.h"

#include "BaconBox/Helper/Flash/FlashHelper.h"

using namespace BaconBox;

void FlashAudio::play(int nbTimes) {
inline_as3("import flash.events.Event; \n");
	if(nbTimes == 0) return;
	this->resetPosition();
	currentState = AudioState::PLAYING;
	this->nbTimes = nbTimes;
	soundChannel = FlashHelper::callMethod(sound, "play", 0, NULL);

	if(this->nbTimes != 0 ){
		AS3::local::var args[2];
		AS3_GetVarxxFromVar(args[0], Event.SOUND_COMPLETE);
		args[1] = loopEventListenerAS3;
		FlashHelper::callMethod(soundChannel, "addEventListener", 2, args);
	}
}


 AS3::local::var FlashAudio::loopEventListener(void *arg, AS3::local::var as3Args){
 	inline_as3("import flash.events.Event; \n");
 	FlashAudio* soundFX = reinterpret_cast<FlashAudio*>(arg);
 	soundFX->resetPosition();
	AS3::local::var event = FlashHelper::callMethod(as3Args, "pop", 0, NULL);
	AS3::local::var currentTarget = FlashHelper::getProperty(event, "currentTarget");
	AS3::local::var args[2];
	AS3_GetVarxxFromVar(args[0], Event.SOUND_COMPLETE);
	args[1] = soundFX->loopEventListenerAS3;
	FlashHelper::callMethod(currentTarget, "removeEventListener", 2, args);
	if(soundFX->nbTimes != LOOPING){
		soundFX->nbTimes--;
	}
	if(soundFX->nbTimes !=0){
		soundFX->play(soundFX->nbTimes);
	}
	return AS3::local::internal::_null; 
}

void FlashAudio::resetPosition(){
	position = AS3::local::internal::new_Number(0);
}

void FlashAudio::stop() {
	if(currentState == AudioState::PLAYING){
		FlashHelper::callMethod(soundChannel, "stop", 0, NULL);
	}
	resetPosition();
	currentState = AudioState::STOPPED;
}

void FlashAudio::pause() {
 	inline_as3("import flash.events.Event; \n");
	if(currentState != AudioState::PLAYING) return;

	AS3::local::var args[2];
	AS3_GetVarxxFromVar(args[0], Event.SOUND_COMPLETE);
	args[1] = this->loopEventListenerAS3;
	FlashHelper::callMethod(soundChannel, "removeEventListener", 2, args);

	position = FlashHelper::getProperty(soundChannel, "position");
	FlashHelper::callMethod(soundChannel, "stop", 0, NULL);
	currentState = AudioState::PAUSED;
}


void FlashAudio::resume() {
 	inline_as3("import flash.events.Event; \n");
	if(currentState == AudioState::PAUSED){
		if(nbTimes == 0) return;
			currentState = AudioState::PLAYING;
			AS3::local::var args[2];
			args[0] = position;
			soundChannel = FlashHelper::callMethod(sound, "play", 1, args);

			AS3_GetVarxxFromVar(args[0], Event.SOUND_COMPLETE);
			args[1] = loopEventListenerAS3;
			FlashHelper::callMethod(soundChannel, "addEventListener", 2, args);
	}
}

bool FlashAudio::isLooping() {
	return (nbTimes == LOOPING);
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

FlashAudio::FlashAudio() :SoundFX(), BackgroundMusic(), currentState(AudioState::INITIAL){
		loopEventListenerAS3 =AS3::local::internal::new_Function(loopEventListener, reinterpret_cast<void*>(this));
}
