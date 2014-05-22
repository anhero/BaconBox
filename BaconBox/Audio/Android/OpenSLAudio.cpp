#include "BaconBox/Audio/Android/OpenSLAudio.h"

#include "BaconBox/Console.h"
#include <assert.h>
#include "BaconBox/Core/Engine.h"
#include "BaconBox/Audio/MusicEngine.h"
#include "BaconBox/Audio/SoundEngine.h"
#include "BaconBox/Audio/Android/OpenSLEngine.h"
using namespace BaconBox;

void OpenSLAudio::play(int nbTimes) {
	if(!playerObject) return;
    SLresult result;

	result = (*playerPlay)->SetPlayState(playerPlay, SL_PLAYSTATE_STOPPED);
		assert(SL_RESULT_SUCCESS == result);
	    (void)result; 

    result = (*playerPlay)->SetPlayState(playerPlay, SL_PLAYSTATE_PLAYING);
        assert(SL_RESULT_SUCCESS == result);
        (void)result; 


	this->nbTimes = nbTimes;
	nbRemainingTimes = nbTimes;
	if(nbTimes == -1){
	    // enable whole file looping
	    result = (*playerSeek)->SetLoop(playerSeek, SL_BOOLEAN_TRUE, 0, SL_TIME_UNKNOWN);
	    assert(SL_RESULT_SUCCESS == result);
	    (void)result;   

	    result = (*playerPlay)->SetCallbackEventsMask(playerPlay, 0);
	    assert(SL_RESULT_SUCCESS == result);
	    (void)result;   

	}
	else{

		result = (*playerPlay)->SetCallbackEventsMask(playerPlay, SL_PLAYEVENT_HEADATEND);
	    assert(SL_RESULT_SUCCESS == result);
	    (void)result;  

	     
	}
}

void OpenSLAudio::stop() {
	if(!playerObject) return;

    SLresult result;

	result = (*playerPlay)->SetPlayState(playerPlay, SL_PLAYSTATE_STOPPED);
		assert(SL_RESULT_SUCCESS == result);
	    (void)result; 
}

void OpenSLAudio::pause() {
	if(!playerObject) return;
    SLresult result;

    result = (*playerPlay)->SetPlayState(playerPlay, SL_PLAYSTATE_PLAYING);
        assert(SL_RESULT_SUCCESS == result);
        (void)result; 

}

void OpenSLAudio::resume() {
	if(!playerObject) return;
    SLresult result;

    result = (*playerPlay)->SetPlayState(playerPlay, SL_PLAYSTATE_PLAYING);
        assert(SL_RESULT_SUCCESS == result);
        (void)result; 
}

bool OpenSLAudio::isLooping() {
	if(!playerObject) return false;
    SLresult result;
	SLboolean looping;
	SLmillisecond *pStartPos;
   	SLmillisecond *pEndPos;
	result = (*playerSeek)->GetLoop(playerSeek, &looping, pStartPos, pEndPos);
    assert(SL_RESULT_SUCCESS == result);
	return looping == SL_BOOLEAN_TRUE;
}

AudioState::type OpenSLAudio::getCurrentState() const {
	if(!playerObject)  return AudioState::STOPPED;
	AudioState::type state;
    SLresult result;
    SLuint32 pState;
    result = (*playerPlay)->GetPlayState(playerPlay, &pState);
	assert(SL_RESULT_SUCCESS == result);
    (void)result; 

    if(pState == SL_PLAYSTATE_STOPPED){
    	state = AudioState::STOPPED;
    }
    else if(pState == SL_PLAYSTATE_PAUSED){
    	state = AudioState::PAUSED;
    }
    else if(pState == SL_PLAYSTATE_PLAYING){
    	state = AudioState::PLAYING;
    }

	return state;
}

void OpenSLAudio::play(int nbTimes, double fadeIn) {
	PRLN("STUB OpenSLAudio::play(int nbTimes, double fadeIn)")
}

void OpenSLAudio::stop(double fadeOut) {
	PRLN("STUB OpenSLAudio::stop(double fadeOut)");
}

void OpenSLAudio::pause(double fadeOut) {
	PRLN("STUB OpenSLAudio::pause(double fadeOut)");
}

void OpenSLAudio::resume(double fadeIn) {
	PRLN("STUB OpenSLAudio::resume(double fadeIn)");

}

OpenSLAudio::~OpenSLAudio() {
	if(playerObject)(*playerObject)->Destroy(playerObject);
	playerObject = NULL;


    if(isMusic){
    	engine->musicVolumeChange.disconnect(this);
    }
    else{
    	engine->soundVolumeChange.disconnect(this);
    }
}


void OpenSLAudio::setVolume(int newVolume){
	SoundFX::setVolume(newVolume);
	BackgroundMusic::setVolume(newVolume);
	if(!playerObject) return;
    SLresult result;

    float engineVolume = (isMusic ? Engine::getMusicEngine().getMusicVolume(): Engine::getSoundEngine().getSoundVolume())/100;

    result = (*playerVolume)->SetVolumeLevel(playerVolume, (maxLvl - SL_MILLIBEL_MIN) * (SoundFX::volume/100) * engineVolume + SL_MILLIBEL_MIN);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;
}
void OpenSLAudio::soundEngineVolumeChanged(){
	setVolume(SoundFX::getVolume());
}

void OpenSLAudio::musicEngineVolumeChanged(){
	setVolume(BackgroundMusic::getVolume());
}


void OpenSLAudio::playCallback(SLPlayItf caller, void *pContext, SLuint32 event){
	OpenSLAudio* audio = reinterpret_cast<OpenSLAudio*>(pContext);
	if(event == SL_PLAYEVENT_HEADATEND){
		audio->nbRemainingTimes--;
		if(audio->nbRemainingTimes > 0){
			audio->play(audio->nbRemainingTimes);
		}
		else{
			audio->stop();
		}

	}
}

void OpenSLAudio::load(bool isMusic, OpenSLEngine* engine, const std::string &path, SLObjectItf engineObject, SLEngineItf engineEngine, SLObjectItf outputMixObject){
    this->isMusic = isMusic;
    this->engine = engine;

    if(isMusic){
    	engine->musicVolumeChange.connect(this, &OpenSLAudio::musicEngineVolumeChanged);
    }
    else{
    	engine->soundVolumeChange.connect(this, &OpenSLAudio::soundEngineVolumeChanged);
    }
    SLresult result;

    // configure audio source
	SLDataLocator_URI loc_fd = {SL_DATALOCATOR_URI , (SLchar*)path.c_str()};
	SLDataFormat_MIME format_mime = {SL_DATAFORMAT_MIME, NULL, SL_CONTAINERTYPE_UNSPECIFIED};
    SLDataSource audioSrc = {&loc_fd, &format_mime};

    // configure audio sink
    SLDataLocator_OutputMix loc_outmix = {SL_DATALOCATOR_OUTPUTMIX, outputMixObject};
    SLDataSink audioSnk = {&loc_outmix, NULL};



    // create audio player
    const SLInterfaceID ids[3] = {SL_IID_SEEK, SL_IID_MUTESOLO, SL_IID_VOLUME};
    const SLboolean req[3] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE};
    result = (*engineEngine)->CreateAudioPlayer(engineEngine, &playerObject, &audioSrc, &audioSnk,
            3, ids, req);
    if(SL_RESULT_SUCCESS != result){
    	playerObject = NULL;
    	Console__error("Error creating the player object in OpenSLAudio::load. Result: " << result);
    }
    else{


  //   	SLAndroidConfigurationItf playerConfig;
		// result = (*playerObject)->GetInterface(playerObject, SL_IID_ANDROIDCONFIGURATION, &playerConfig);
		// assert(SL_RESULT_SUCCESS == result);
		// SLint32 streamType = SL_ANDROID_STREAM_ALARM;
		// result = (*playerConfig)->SetConfiguration(playerConfig, SL_ANDROID_KEY_STREAM_TYPE, &streamType, sizeof(SLint32));
		// assert(SL_RESULT_SUCCESS == result);



	    // realize the player
	    result = (*playerObject)->Realize(playerObject, SL_BOOLEAN_FALSE);
	    assert(SL_RESULT_SUCCESS == result);
	    (void)result;

	    // get the play interface
	    result = (*playerObject)->GetInterface(playerObject, SL_IID_PLAY, &playerPlay);
	    assert(SL_RESULT_SUCCESS == result);
	    (void)result;

	    // get the seek interface
	    result = (*playerObject)->GetInterface(playerObject, SL_IID_SEEK, &playerSeek);
	    assert(SL_RESULT_SUCCESS == result);
	    (void)result;

	    // get the mute/solo interface
	    result = (*playerObject)->GetInterface(playerObject, SL_IID_MUTESOLO, &playerMuteSolo);
	    assert(SL_RESULT_SUCCESS == result);
	    (void)result;

	    // get the volume interface
	    result = (*playerObject)->GetInterface(playerObject, SL_IID_VOLUME, &playerVolume);
	    assert(SL_RESULT_SUCCESS == result);
	    (void)result;



	    result = (*playerVolume)->GetMaxVolumeLevel(playerVolume, &maxLvl);
	    assert(SL_RESULT_SUCCESS == result);
	    (void)result;

	    result = (*playerPlay)->RegisterCallback(playerPlay, OpenSLAudio::playCallback, this);
	    assert(SL_RESULT_SUCCESS == result);
	    (void)result; 

    	setVolume(BackgroundMusic::getVolume());

	}
}

OpenSLAudio::OpenSLAudio() : BackgroundMusic(), SoundFX(), sigly::HasSlots<SIGLY_DEFAULT_MT_POLICY>()  {
}
