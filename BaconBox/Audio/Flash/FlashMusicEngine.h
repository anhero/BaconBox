/**
 * @file
 * @ingroup Audio
 */
#ifndef BB_FLASH_AUDIO_ENGINE_H
#define BB_FLASH_AUDIO_ENGINE_H

#include <list>

#include "BaconBox/Audio/SoundEngine.h"
#include "BaconBox/Audio/MusicEngine.h"

#include <AS3/AS3.h>
#include <AS3/AS3++.h>

namespace BaconBox {
	class FlashBackgroundMusic;
	class FlashBackgroundMusic;

	class FlashMusicEngine : public MusicEngine {
		friend class AudioEngine;
                friend class BaseEngine;
                friend class ResourceManager;
	public:

		static FlashMusicEngine& getInstance();


		BackgroundMusic* getBackgroundMusic(const std::string& key,
		                                    bool survive = true);
	private:
		std::list<FlashBackgroundMusic*> audios;


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
