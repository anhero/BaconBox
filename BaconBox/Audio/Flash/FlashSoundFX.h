/**
 * @file
 * @ingroup Audio
 */
#ifndef BB_FLASH_SOUNDFX_H
#define BB_FLASH_SOUNDFX_H

#include "BaconBox/Audio/BackgroundMusic.h"
#include "BaconBox/Audio/SoundFX.h"

#include <AS3/AS3.h>
#include <AS3/AS3++.h>

namespace BaconBox {

	class FlashSoundFX : public SoundFX  {
		friend class AudioEngine;
		friend class FlashAudioEngine;
	public:
		void play(int nbTimes);

		void stop();

		void pause();

		void resume();

		bool isLooping();

		AudioState getCurrentState() const;

		void play(int nbTimes, double fadeIn);

		void stop(double fadeOut);

		void pause(double fadeOut);

		void resume(double fadeIn);

		virtual ~FlashSoundFX();

		FlashSoundFX();

	private:
		AS3::local::var sound;
		AS3::local::var soundChannel;
	};
}

#endif
