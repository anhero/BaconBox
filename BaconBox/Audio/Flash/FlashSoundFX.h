/**
 * @file
 * @ingroup Audio
 */
#ifndef BB_FLASH_SOUNDFX_H
#define BB_FLASH_SOUNDFX_H

#include "BaconBox/Audio/SoundFX.h"

#include <AS3/AS3.h>
#include <AS3/AS3++.h>

namespace BaconBox {

	class FlashSoundFX : public SoundFX {
		friend class AudioEngine;
		friend class FlashSoundEngine;
	public:
		void play(int nbTimes);

		void stop();

		void pause();

		void resume();

		bool isLooping();

		void setVolume(int newVolume);

		AudioState getCurrentState() const;

		virtual ~FlashSoundFX();

		FlashSoundFX();

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
