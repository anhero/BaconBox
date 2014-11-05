#include "BaconBox/Audio/Flash/FlashSoundEngine.h"

#include "BaconBox/Console.h"

#include "BaconBox/Audio/SoundInfo.h"
#include "BaconBox/Audio/MusicInfo.h"
#include "BaconBox/Audio/Flash/FlashSoundFX.h"

#include "BaconBox/ResourceManager.h"
#include "BaconBox/Helper/Flash/FlashHelper.h"
#include "BaconBox/Core/Engine.h"

using namespace BaconBox;



BB_SINGLETON_IMPL(FlashSoundEngine);


SoundFX* FlashSoundEngine::getSoundFX(const std::string& key, bool survive) {
	FlashSoundFX* result = new FlashSoundFX();

	if(result) {
		SoundInfo* info = ResourceManager::getSound(key);

		if(info) {
			result->sound = info->sound;
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



FlashSoundEngine::FlashSoundEngine() : SoundEngine(){
	Console::println("FlashSoundEngine::FlashSoundEngine()");
}

FlashSoundEngine::~FlashSoundEngine() {
	Console::println("FlashSoundEngine::~FlashSoundEngine()");
}

void FlashSoundEngine::update() {
	//For each sound (music or sound effect).
	std::list<FlashSoundFX*>::iterator i = audios.begin();
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

void FlashSoundEngine::setSoundVolume(int newSoundVolume) {
		this->SoundEngine::setSoundVolume(newSoundVolume);

		if (!this->SoundEngine::isMuted()) {
			soundVolumeChange();
		}
	}

SoundInfo* FlashSoundEngine::loadSound(const std::string& filePath) {
	Console::println(" FlashSoundEngine::loadSound not implemented.");
	return new SoundInfo();
}

SoundInfo* FlashSoundEngine::loadSound(const SoundParameters& params) {
	Console::println("FlashSoundEngine::loadSound not implemented.");
	return new SoundInfo();
}

bool FlashSoundEngine::unloadSound(SoundInfo* sound) {
	Console::println("FlashSoundEngine::unloadSound(sound: " +
				   Console::toString(sound) + ")");
	return true;
}

SoundInfo* FlashSoundEngine::loadSoundFromBundle(const std::string& bundleKey){
	
	SoundInfo *result = new SoundInfo();

	result->sound = FlashHelper::construct(bundleKey);
	return result;

}

