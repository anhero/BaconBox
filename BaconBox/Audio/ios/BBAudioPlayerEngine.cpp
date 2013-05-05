#include "BaconBox/PlatformFlagger.h"

#include "BaconBox/Audio/ios/BBAudioPlayerEngine.h"

#include "BaconBox/Audio/ios/BBAudioPlayerMusic.h"
#include "BaconBox/Audio/MusicInfo.h"
#include "BaconBox/ResourceManager.h"
#include "BaconBox/Audio/AudioState.h"
#include "BaconBox/Audio/NullAudio.h"

#include "BaconBox/Console.h"

namespace BaconBox {
	BackgroundMusic* BBAudioPlayerEngine::getBackgroundMusic(std::string const &key,
															 bool survive) {
		MusicInfo* bgmInfo = ResourceManager::getMusic(key);
		if(bgmInfo) {
			BBAudioPlayerMusic* bgm = new BBAudioPlayerMusic();
			bgm->load(bgmInfo->filePath);
			if (!survive) {
				managedMusics.push_back(bgm);
			}
			return bgm;
		} else {
			NullAudio* nullAudio = new NullAudio();
			if(!survive) {
				managedMusics.push_back(nullAudio);
			}
			return nullAudio;
		}
	}
	
	void BBAudioPlayerEngine::setMusicVolume(int newMusicVolume) {
		this->MusicEngine::setMusicVolume(newMusicVolume);
		BBAudioPlayerMusic::refreshVolume();
	}
	
	BBAudioPlayerEngine::BBAudioPlayerEngine(): MusicEngine() {
	}
	
	BBAudioPlayerEngine::~BBAudioPlayerEngine() {
	}
	
	void BBAudioPlayerEngine::update() {
		for (std::list<BackgroundMusic*>::iterator i = managedMusics.begin();
			 i != managedMusics.end(); i++) {
			// If the music is at stopped, we delete it.
			if((*i)->getCurrentState() == AudioState::STOPPED) {
				delete *i;
				managedMusics.erase(i);
			}
		}
	}
	
	MusicInfo* BBAudioPlayerEngine::loadMusic(const std::string& filePath) {
		MusicInfo* result = new MusicInfo();
		result->filePath = filePath;
		return result;
	}
	
	MusicInfo* BBAudioPlayerEngine::loadMusic(const MusicParameters& params) {
		MusicInfo* result = new MusicInfo();
		result->filePath = params.filePath;
		return result;
	}
	
	bool BBAudioPlayerEngine::unloadMusic(MusicInfo* music) {
		return true;
	}
}
