#include "BaconBox/Audio/Flash/FlashBackgroundMusic.h"

#include "BaconBox/Console.h"

#include "BaconBox/Helper/Flash/FlashHelper.h"

#include "BaconBox/Helper/Ease.h"

using namespace BaconBox;

void FlashBackgroundMusic::play(int nbTimes) {
inline_as3("import flash.events.Event; \n");
	if(nbTimes == 0) return;
	this->resetPosition();
	this->nbTimes = nbTimes;
	currentState = AudioState::PLAYING;
	soundChannel = FlashHelper::callMethod(sound, "play", 0, NULL);
	FlashHelper::setProperty(soundChannel, "soundTransform", soundTransform);
	if(this->nbTimes != 0 ){
		AS3::local::var args[2];
		AS3_GetVarxxFromVar(args[0], Event.SOUND_COMPLETE);
		args[1] = loopEventListenerAS3;
		FlashHelper::callMethod(soundChannel, "addEventListener", 2, args);
	}
}


 AS3::local::var FlashBackgroundMusic::loopEventListener(void *arg, AS3::local::var as3Args){
 	inline_as3("import flash.events.Event; \n");
 	FlashBackgroundMusic* music = reinterpret_cast<FlashBackgroundMusic*>(arg);
 	music->resetPosition();
	AS3::local::var event = FlashHelper::callMethod(as3Args, "pop", 0, NULL);
	AS3::local::var currentTarget = FlashHelper::getProperty(event, "currentTarget");
	AS3::local::var args[2];
	AS3_GetVarxxFromVar(args[0], Event.SOUND_COMPLETE);
	args[1] = music->loopEventListenerAS3;
	FlashHelper::callMethod(currentTarget, "removeEventListener", 2, args);
	if(music->nbTimes != LOOPING){
		music->nbTimes--;
	}
	if(music->nbTimes !=0){
		music->play(music->nbTimes);
	}
	return AS3::local::internal::_null; 
}

void FlashBackgroundMusic::resetPosition(){
	playPosition = AS3::local::internal::new_Number(0);
}

void FlashBackgroundMusic::stop() {
	if(currentState == AudioState::PLAYING){
		FlashHelper::callMethod(soundChannel, "stop", 0, NULL);
	}
	resetPosition();
	currentState = AudioState::STOPPED;
}

void FlashBackgroundMusic::update(){
	if(currentState == AudioState::FADING_IN){
		if(fadeTween.isDone()){
			currentState = AudioState::PLAYING;
		}
		setFlashVolume(fadeTween.getValue());
	}
	else if(currentState == AudioState::FADING_OUT){
		if(fadeTween.isDone()){
			if(isStopping){
				stop();
				isStopping = false;
			}
			else{
				pause();
			}
		}
		setFlashVolume(fadeTween.getValue());
	}
	
}


void FlashBackgroundMusic::pause() {
 	inline_as3("import flash.events.Event; \n");
	if(currentState != AudioState::PLAYING) return;

	AS3::local::var args[2];
	AS3_GetVarxxFromVar(args[0], Event.SOUND_COMPLETE);
	args[1] = this->loopEventListenerAS3;
	FlashHelper::callMethod(soundChannel, "removeEventListener", 2, args);

	playPosition = FlashHelper::getProperty(soundChannel, "position");
	FlashHelper::callMethod(soundChannel, "stop", 0, NULL);
	currentState = AudioState::PAUSED;
}


void FlashBackgroundMusic::setVolume(int newVolume){
	BackgroundMusic::setVolume(newVolume);
	setFlashVolume(this->volume);
}

void FlashBackgroundMusic::setFlashVolume(int newVolume){
	FlashHelper::setProperty(soundTransform, "volume", AS3::local::internal::new_Number((float)newVolume/MAX_VOLUME));
	FlashHelper::setProperty(soundChannel, "soundTransform", soundTransform);
}


void FlashBackgroundMusic::resume() {
 	inline_as3("import flash.events.Event; \n");
	if(currentState == AudioState::PAUSED){
		if(nbTimes == 0) return;
			currentState = AudioState::PLAYING;
			AS3::local::var args[2];
			args[0] = playPosition;
			soundChannel = FlashHelper::callMethod(sound, "play", 1, args);
			FlashHelper::setProperty(soundChannel, "soundTransform", soundTransform);
			AS3_GetVarxxFromVar(args[0], Event.SOUND_COMPLETE);
			args[1] = loopEventListenerAS3;
			FlashHelper::callMethod(soundChannel, "addEventListener", 2, args);
	}
}

bool FlashBackgroundMusic::isLooping() {
	return (nbTimes == LOOPING);
}

AudioState FlashBackgroundMusic::getCurrentState() const {
	Console::println("Getting a FlashBackgroundMusic object's audio state, returning STOPPED");
	return currentState;
}

void FlashBackgroundMusic::play(int nbTimes, double fadeIn) {
	fadeTween = Tween<int>(0, this->volume, fadeIn, Ease::LINEAR);
	play(nbTimes);
	setFlashVolume(0);
	currentState = AudioState::FADING_IN;
	fadeTween.start();
}

void FlashBackgroundMusic::stop(double fadeOut) {
	fadeTween = Tween<int>(this->volume, 0, fadeOut, Ease::LINEAR);
	isStopping = true;
	currentState = AudioState::FADING_OUT;
	fadeTween.start();
}

void FlashBackgroundMusic::pause(double fadeOut) {
	fadeTween = Tween<int>(this->volume, 0, fadeOut, Ease::LINEAR);
	isStopping = false;
	currentState = AudioState::FADING_OUT;
	fadeTween.start();
}

void FlashBackgroundMusic::resume(double fadeIn) {
	fadeTween = Tween<int>(0, this->volume, fadeIn, Ease::LINEAR);
	setFlashVolume(0);
	currentState = AudioState::FADING_IN;
	fadeTween.start();
}

FlashBackgroundMusic::~FlashBackgroundMusic() {
	Console::println("Destroying a FlashBackgroundMusic object.");
}

FlashBackgroundMusic::FlashBackgroundMusic() :BackgroundMusic(), currentState(AudioState::INITIAL){
		loopEventListenerAS3 =AS3::local::internal::new_Function(loopEventListener, reinterpret_cast<void*>(this));
		soundTransform = FlashHelper::construct("flash.media.SoundTransform");
}
