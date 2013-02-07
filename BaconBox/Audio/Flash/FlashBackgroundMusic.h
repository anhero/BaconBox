/**
 * @file
 * @ingroup Audio
 */
#ifndef BB_FLASH_BACKGROUNDMUSIC_H
#define BB_FLASH_BACKGROUNDMUSIC_H

#include "BaconBox/Audio/BackgroundMusic.h"

#include <AS3/AS3.h>
#include <AS3/AS3++.h>

namespace BaconBox {

	class FlashBackgroundMusic : public BackgroundMusic {
		friend class AudioEngine;
		friend class FlashMusicEngine;
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

		void setVolume(int newVolume);


		virtual ~FlashBackgroundMusic();

		FlashBackgroundMusic();

	private:
		int nbTimes;
		AS3::local::var sound;
		AS3::local::var soundChannel;
		AS3::local::var soundTransform;
		AS3::local::var loopEventListenerAS3;
		static const int LOOPING = -1;
		static AS3::local::var loopEventListener(void *arg, AS3::local::var as3Args);

		AudioState currentState;

		AS3::local::var position;

		void resetPosition();
	};
}

#endif
