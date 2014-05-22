#include "BaconBox/Audio/Android/OpenSLEngine.h"

#include "BaconBox/Console.h"

#include "BaconBox/Audio/SoundInfo.h"
#include "BaconBox/Audio/MusicInfo.h"
#include "BaconBox/Audio/Android/OpenSLAudio.h"
#include "BaconBox/ResourceManager.h"

using namespace BaconBox;

OpenSLEngine& OpenSLEngine::getInstance() {
	static OpenSLEngine instance;
	return instance;
}

SoundFX* OpenSLEngine::getSoundFX(const std::string& key, bool survive) {
	OpenSLAudio* result = new OpenSLAudio();

	if(result) {
		SoundInfo* info = ResourceManager::getSound(key);
		if(info) {
			result->load(false, this, info->filePath, engineObject, engineEngine, outputMixObject);
		} else {
			delete result;
			result = NULL;
			Console::println("Tried to get a sound effect from an invalid key: " +
						   key);
		}

		if(!survive) {
			audios.push_back(result);
		}
	} else {
		Console::println("Failed to allocate memory for the new sound effect: " +
					   key);
	}

	return result;
}


void OpenSLEngine::setMusicVolume(int newMusicVolume) {
	this->MusicEngine::setMusicVolume(newMusicVolume);
	musicVolumeChange();
	
}

void OpenSLEngine::setSoundVolume(int newSoundVolume) {
	this->SoundEngine::setSoundVolume(newSoundVolume);
	soundVolumeChange();
}


BackgroundMusic* OpenSLEngine::getBackgroundMusic(const std::string& key,
													 bool survive) {
	OpenSLAudio* result = new OpenSLAudio();

	if(result) {
		MusicInfo* info = ResourceManager::getMusic(key);

		if(info) {
			result->load(true, this, info->filePath, engineObject, engineEngine, outputMixObject);

		} else {
			delete result;
			result = NULL;
			Console::println("Tried to get a music from an invalid key: " + key);
		}

		if(!survive) {
			audios.push_back(result);
		}
	} else {
		Console::println("Failed to allocate memory for the new music: " + key);
	}

	return result;
}

OpenSLEngine::OpenSLEngine() : SoundEngine(), MusicEngine() {
    SLresult result;

    // create engine
    result = slCreateEngine(&engineObject, 0, NULL, 0, NULL, NULL);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // realize the engine
    result = (*engineObject)->Realize(engineObject, SL_BOOLEAN_FALSE);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // get the engine interface, which is needed in order to create other objects
    result = (*engineObject)->GetInterface(engineObject, SL_IID_ENGINE, &engineEngine);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // create output mix
    result = (*engineEngine)->CreateOutputMix(engineEngine, &outputMixObject, 0, NULL, NULL);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // realize the output mix
    result = (*outputMixObject)->Realize(outputMixObject, SL_BOOLEAN_FALSE);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;
 }

OpenSLEngine::~OpenSLEngine() {
	(*outputMixObject)->Destroy(outputMixObject);
	(*engineObject)->Destroy(engineObject);
}

void OpenSLEngine::update() {
	// For each sound (music or sound effect).
	std::list<OpenSLAudio*>::iterator i = audios.begin();
	while(i != audios.end()) {
		// We make sure the pointer is valid.
		if(*i) {
			if((*i)->getCurrentState() == AudioState::STOPPED) {
				delete *i;
				i = audios.erase(i);
			} else {
				++i;
			}
		} else {
			// If the pointer is invalid (which should not happen), we remove
			// it from the list.
			i = audios.erase(i);
		}
	}
}

bool OpenSLEngine::managedByEngine(){
	return false;
}


SoundInfo* OpenSLEngine::loadSound(const std::string& filePath) {
	SoundInfo *result = new SoundInfo();
	result->filePath = filePath;

	return result;
}

SoundInfo* OpenSLEngine::loadSound(const SoundParameters& params) {
		return loadSound(params.path);
}

bool OpenSLEngine::unloadSound(SoundInfo* sound) {
	Console::println("OpenSLEngine::unloadSound(sound: " +
				   Console::toString(sound) + ")");
	return true;
}

MusicInfo* OpenSLEngine::loadMusic(const std::string& filePath) {
	MusicInfo *result = new MusicInfo();
	result->filePath = filePath;

	return result;
}

MusicInfo* OpenSLEngine::loadMusic(const MusicParameters& params) {
	return loadMusic(params.filePath);
}

bool OpenSLEngine::unloadMusic(MusicInfo* music) {
	Console::println("OpenSLEngine::unloadMusic(music: " +
				   Console::toString(music) + ")");
	return true;
}

