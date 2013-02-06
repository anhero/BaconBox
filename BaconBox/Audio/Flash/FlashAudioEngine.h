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
	class FlashAudio;

	class FlashAudioEngine : public SoundEngine, public MusicEngine {
		friend class AudioEngine;
                friend class BaseEngine;
                friend class ResourceManager;
	public:

		static FlashAudioEngine& getInstance();

		SoundFX* getSoundFX(const std::string& key, bool survive = true);

		BackgroundMusic* getBackgroundMusic(const std::string& key,
		                                    bool survive = true);
	private:
		std::list<FlashAudio*> audios;

		FlashAudioEngine();

		~FlashAudioEngine();

		void update();

		SoundInfo* loadSoundFromBundle(const std::string& bundleKey);

		SoundInfo* loadSound(const std::string& filePath);

		SoundInfo* loadSound(const SoundParameters& params);

		bool unloadSound(SoundInfo* sound);

		MusicInfo* loadMusic(const std::string& filePath);

		MusicInfo* loadMusic(const MusicParameters& params);
		MusicInfo* loadMusicFromBundle(const std::string& bundleKey);

		bool unloadMusic(MusicInfo* music);
	};
}

#endif
