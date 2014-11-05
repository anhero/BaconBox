/**
 * @file
 * @ingroup Audio
 */
#ifndef BB_FLASH_AUDIO_ENGINE_H
#define BB_FLASH_AUDIO_ENGINE_H

#include <set>
#include <list>
#include "BaconBox/Audio/SoundEngine.h"
#include "BaconBox/Audio/MusicEngine.h"

#include <AS3/AS3.h>
#include <AS3/AS3++.h>
#include <sigly.h>

namespace BaconBox {
	class FlashBackgroundMusic;
	class FlashBackgroundMusic;

	class FlashMusicEngine : public MusicEngine {
		friend class AudioEngine;
		friend class BaseEngine;
		friend class ResourceManager;
		friend class MusicEngine;
		BB_SINGLETON_DECL(FlashMusicEngine);
	public:

		sigly::Signal0<> musicVolumeChange;


		BackgroundMusic* getBackgroundMusic(const std::string& key,
		                                    bool survive = true);


		void setMusicVolume(int newMusicVolume);

	private:
		std::set<FlashBackgroundMusic*> audios;
		std::list<FlashBackgroundMusic*> audiosToBeDeleted;

		FlashMusicEngine();

		~FlashMusicEngine();

		void update();

		MusicInfo* loadMusic(const std::string& filePath);

		MusicInfo* loadMusic(const MusicParameters& params);
		MusicInfo* loadMusicFromBundle(const std::string& bundleKey);

		bool unloadMusic(MusicInfo* music);
	};
}

#endif
