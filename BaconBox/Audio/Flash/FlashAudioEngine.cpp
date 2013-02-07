#include "BaconBox/Audio/Flash/FlashAudioEngine.h"

#include "BaconBox/Console.h"

#include "BaconBox/Audio/SoundInfo.h"
#include "BaconBox/Audio/MusicInfo.h"
#include "BaconBox/Audio/Flash/FlashAudio.h"

#include "BaconBox/ResourceManager.h"
#include "BaconBox/Helper/Flash/FlashHelper.h"

using namespace BaconBox;

FlashAudioEngine& FlashAudioEngine::getInstance() {
	static FlashAudioEngine instance;
	return instance;
}

SoundFX* FlashAudioEngine::getSoundFX(const std::string& key, bool survive) {
	FlashAudio* result = new FlashAudio();

	if(result) {
		SoundInfo* info = ResourceManager::getSound(key);

		if(info) {
			result->sound = info->sound;
		} else {
			delete result;
			result = NULL;
			Console::println("Tried to get a sound effect from an invalid key: " +
						   key);
			Console::printTrace();
		}

		if(!survive) {
			audio.push_back(result);
		}
	} else {
		Console::println("Failed to allocate memory for the new sound effect: " +
					   key);
		Console::printTrace();
	}

	return result;
}




BackgroundMusic* FlashAudioEngine::getBackgroundMusic(const std::string& key,
													 bool survive) {
		PV(key);
	FlashAudio* result = new FlashAudio();
		PV(result);

	if(result) {
		MusicInfo* info = ResourceManager::getMusic(key);
		PV(info);

		if(info) {
			result->sound = info->sound;

		} else {
			delete result;
			result = NULL;
			Console::println("Tried to get a music from an invalid key: " + key);
			Console::printTrace();
		}

		if(!survive) {
			audio.push_back(result);
		}
	} else {
		Console::println("Failed to allocate memory for the new music: " + key);
		Console::printTrace();
	}

	return result;
}

FlashAudioEngine::FlashAudioEngine() : SoundEngine(),MusicEngine(){
	Console::println("FlashAudioEngine::FlashAudioEngine()");
}

FlashAudioEngine::~FlashAudioEngine() {
	Console::println("FlashAudioEngine::~FlashAudioEngine()");
}

void FlashAudioEngine::update() {
	// For each sound (music or sound effect).
	// std::list<FlashAudio*>::iterator i = audios.begin();
	// while(i != audios.end()) {
	// 	// We make sure the pointer is valid.
	// 	if(*i) {
	// 		if((*i)->getCurrentState() == AudioState::STOPPED) {
	// 			delete *i;
	// 			i = audios.erase(i);
	// 		} else {
	// 			++i;
	// 		}
	// 	} else {
	// 		// If the pointer is invalid (which should not happen), we remove
	// 		// it from the list.
	// 		i = audios.erase(i);
	// 	}
	// }
}

SoundInfo* FlashAudioEngine::loadSound(const std::string& filePath) {
	Console::println("FlashAudioEngine::loadSound(filePath: " + filePath + ")");
	return new SoundInfo();
}

SoundInfo* FlashAudioEngine::loadSound(const SoundParameters& params) {
	Console::println("FlashAudioEngine::loadSound(params.name: " + params.name +
				   ")");
	return new SoundInfo();
}

bool FlashAudioEngine::unloadSound(SoundInfo* sound) {
	Console::println("FlashAudioEngine::unloadSound(sound: " +
				   Console::toString(sound) + ")");
	return true;
}

MusicInfo* FlashAudioEngine::loadMusic(const std::string& filePath) {
	Console::println("FlashAudioEngine::loadMusic(filePath: " + filePath + ")");
	return new MusicInfo();
}

MusicInfo* FlashAudioEngine::loadMusic(const MusicParameters& params) {
	Console::println("FlashAudioEngine::loadMusic(params.name: " + params.name +
				   ")");
	return new MusicInfo();
}

SoundInfo* FlashAudioEngine::loadSoundFromBundle(const std::string& bundleKey){
	
	SoundInfo *result = new SoundInfo();

	result->sound = FlashHelper::construct(bundleKey);
	return result;

}

MusicInfo* FlashAudioEngine::loadMusicFromBundle(const std::string& bundleKey){
	
	MusicInfo *result = new MusicInfo();

	result->sound = FlashHelper::construct(bundleKey);
	return result;

}

bool FlashAudioEngine::unloadMusic(MusicInfo* music) {
	Console::println("FlashAudioEngine::unloadMusic(music: " +
				   Console::toString(music) + ")");
	return true;
}

