#include "BaconBox/Audio/Flash/FlashSoundFX.h"

#include "BaconBox/Console.h"

#include "BaconBox/Helper/Flash/FlashHelper.h"

using namespace BaconBox;

void FlashSoundFX::play(int nbTimes) {
inline_as3("import flash.events.Event; \n");
	if(nbTimes == 0) return;
	this->resetPosition();
	currentState = AudioState::PLAYING;
	this->nbTimes = nbTimes;
	soundChannel = FlashHelper::callMethod(sound, "play", 0, NULL);
	if(soundChannel == AS3::local::internal::_null){
		soundChannel = FlashHelper::construct("flash.media.SoundChannel");
	}
	FlashHelper::setProperty(soundChannel, "soundTransform", soundTransform);
	if(this->nbTimes != 0 ){
		AS3::local::var args[2];
		AS3_GetVarxxFromVar(args[0], Event.SOUND_COMPLETE);
		args[1] = loopEventListenerAS3;
		FlashHelper::callMethod(soundChannel, "addEventListener", 2, args);
	}
}

void FlashSoundFX::setVolume(int newVolume){
	SoundFX::setVolume(newVolume);
	FlashHelper::setProperty(soundTransform, "volume", AS3::local::internal::new_Number((float)this->volume/MAX_VOLUME));
	FlashHelper::setProperty(soundChannel, "soundTransform", soundTransform);
}



 AS3::local::var FlashSoundFX::loopEventListener(void *arg, AS3::local::var as3Args){
 	inline_as3("import flash.events.Event; \n");
 	FlashSoundFX* soundFX = reinterpret_cast<FlashSoundFX*>(arg);
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

void FlashSoundFX::resetPosition(){
	position = AS3::local::internal::new_Number(0);
}

void FlashSoundFX::stop() {
	if(currentState == AudioState::PLAYING){
		FlashHelper::callMethod(soundChannel, "stop", 0, NULL);
	}
	resetPosition();
	currentState = AudioState::STOPPED;
}

void FlashSoundFX::pause() {
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


void FlashSoundFX::resume() {
 	inline_as3("import flash.events.Event; \n");
	if(currentState == AudioState::PAUSED){
		if(nbTimes == 0) return;
			currentState = AudioState::PLAYING;
			AS3::local::var args[2];
			args[0] = position;
			soundChannel = FlashHelper::callMethod(sound, "play", 1, args);
			if(soundChannel == AS3::local::internal::_null){
				soundChannel = FlashHelper::construct("flash.media.SoundChannel");
			}
			FlashHelper::setProperty(soundChannel, "soundTransform", soundTransform);
			AS3_GetVarxxFromVar(args[0], Event.SOUND_COMPLETE);
			args[1] = loopEventListenerAS3;
			FlashHelper::callMethod(soundChannel, "addEventListener", 2, args);
	}
}

bool FlashSoundFX::isLooping() {
	return (nbTimes == LOOPING);
}

AudioState FlashSoundFX::getCurrentState() const {
	return currentState;
}

FlashSoundFX::~FlashSoundFX() {
	Console::println("Destroying a FlashSoundFX object.");
}

FlashSoundFX::FlashSoundFX() :SoundFX(), currentState(AudioState::INITIAL){
		loopEventListenerAS3 =AS3::local::internal::new_Function(loopEventListener, reinterpret_cast<void*>(this));
		soundTransform = FlashHelper::construct("flash.media.SoundTransform");
}
