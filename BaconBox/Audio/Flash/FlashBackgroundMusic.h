/**
 * @file
 * @ingroup Audio
 */
#ifndef BB_FLASH_BACKGROUNDMUSIC_H
#define BB_FLASH_BACKGROUNDMUSIC_H

#include "BaconBox/Audio/BackgroundMusic.h"
#include "BaconBox/Audio/SoundFX.h"

#include <AS3/AS3.h>
#include <AS3/AS3++.h>

namespace BaconBox {

	class FlashBackgroundMusic : public BackgroundMusic{
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

		virtual ~FlashBackgroundMusic();

		FlashBackgroundMusic();

	private:
		AS3::local::var sound;
		AS3::local::var soundChannel;
	};
}

#endif
