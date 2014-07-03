#include "BaconBox/Audio/Flash/FlashMusicEngine.h"

#include "BaconBox/Console.h"

#include "BaconBox/Audio/SoundInfo.h"
#include "BaconBox/Audio/MusicInfo.h"
#include "BaconBox/Audio/Flash/FlashBackgroundMusic.h"

#include "BaconBox/ResourceManager.h"
#include "BaconBox/Helper/Flash/FlashHelper.h"

using namespace BaconBox;

FlashMusicEngine& FlashMusicEngine::getInstance() {
	static FlashMusicEngine instance;
	return instance;
}




BackgroundMusic* FlashMusicEngine::getBackgroundMusic(const std::string& key,
													 bool survive) {
	FlashBackgroundMusic* result = new FlashBackgroundMusic();
	if(result) {
		MusicInfo* info = ResourceManager::getMusic(key);
		if(info) {
			result->sound = info->sound;

		} else {
			delete result;
			result = NULL;
			Console::println("Tried to get a music from an invalid key: " + key);
			// Console::printTrace();
		}
			audios.insert(result);
		if(!survive) {
			audiosToBeDeleted.push_back(result);
		}
	} else {
		Console::println("Failed to allocate memory for the new music: " + key);
		// Console::printTrace();
	}

	return result;
}

FlashMusicEngine::FlashMusicEngine() : MusicEngine(){
	Console::println("FlashMusicEngine::FlashMusicEngine()");
}

FlashMusicEngine::~FlashMusicEngine() {
	Console::println("FlashMusicEngine::~FlashMusicEngine()");
}

void FlashMusicEngine::update() {
	std::set<FlashBackgroundMusic*>::iterator j = audios.begin();
	while(j != audios.end()) {
		(*j)->update();
		++j;
		
	}	

	 std::list<FlashBackgroundMusic*>::iterator i = audiosToBeDeleted.begin();
	while(i != audiosToBeDeleted.end()) {
		// We make sure the pointer is valid.
		if(*i) {
			if((*i)->getCurrentState() == AudioState::STOPPED) {
				audios.erase(*i);
				delete *i;
				i = audiosToBeDeleted.erase(i);
			} else {
				++i;
			}
		} else {
			// If the pointer is invalid (which should not happen), we remove
			// it from the set.
			i = audiosToBeDeleted.erase(i);
		}
	 }
}


MusicInfo* FlashMusicEngine::loadMusic(const std::string& filePath) {
	Console::println("FlashMusicEngine::loadMusic not implemented.");
	return new MusicInfo();
}

MusicInfo* FlashMusicEngine::loadMusic(const MusicParameters& params) {
	Console::println("FlashMusicEngine::loadMusic not implemented.");
	return new MusicInfo();
}



MusicInfo* FlashMusicEngine::loadMusicFromBundle(const std::string& bundleKey){
	
	MusicInfo *result = new MusicInfo();

	result->sound = FlashHelper::construct(bundleKey);
	return result;

}

bool FlashMusicEngine::unloadMusic(MusicInfo* music) {
	Console::println("FlashMusicEngine::unloadMusic(music: " +
				   Console::toString(music) + ")");
	return true;
}

