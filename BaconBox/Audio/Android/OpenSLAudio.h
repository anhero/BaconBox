/**
 * @file
 * @ingroup Audio
 */
#ifndef BB_OPENSL_AUDIO_H
#define BB_OPENSL_AUDIO_H

#include "BaconBox/Audio/BackgroundMusic.h"
#include "BaconBox/Audio/SoundFX.h"

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include <string>
#include "sigly.h"

namespace BaconBox {
	class OpenSLEngine;
	/**
	 * OpenSL implementation of the sound engine's audio "things".
	 *
	 * Currently pretty much assumes Android's version of OpenSL, but should be
	 * easy to fix for other implementations.
	 *
	 * @ingroup Audio
	 */
	class OpenSLAudio : public BackgroundMusic, public SoundFX, public sigly::HasSlots<SIGLY_DEFAULT_MT_POLICY>  {
		friend class AudioEngine;
		friend class OpenSLEngine;

	public:
		/**
		 * Plays the sound a given number of times.
		 * @param nbTimes Number of times the sound will be played in loop. A
		 * negative number is for infinite looping.
		 */
		void play(int nbTimes);
		/**
		 * Stops the sound. Cannot be resumed and next time it will be played
		 * it will start from the beginning.
		 */
		void stop();
		/**
		 * Pauses the sound. Remembers where it was paused so it can resume when
		 * calling the resume method.
		 */
		void pause();
		/**
		 * Resumes the sound. Will only resume if the sound has been paused.
		 */
		void resume();
		/**
		 * Checks if the sound is currently playing infinitely.
		 * @return True if the sound is currently playing infinitely.
		 */
		bool isLooping();
		/**
		 * Gets the sound's current state. Used to know if it is at its initial
		 * state, currently playing, paused, etc.
		 * @return Sound's current state.
		 * @see BaconBox::AudioState::Enum
		 */
		AudioState::type getCurrentState() const;
		/**
		 * Play the music with a fade in effect.
		 * @param nbTimes Number of times to play the music in loop. Negative
		 * value for infinite looping.
		 * @param fadeIn Time the fade in effect will last (in seconds).
		 */
		void play(int nbTimes, double fadeIn);
		/**
		 * Stops the music with a fade out effect. Cannot be resumed and next
		 * time it will be played it will start from the beginning.
		 * @param fadeOut Time the fade out effect will last (in seconds).
		 */
		void stop(double fadeOut);
		/**
		 * Pauses the music with a fade out effect. Remembers where it was
		 * paused so it can resume when calling the resume method.
		 * @param fadeOut Time the fade out effect will last (in seconds).
		 */
		void pause(double fadeOut);
		/**
		 * Resumes the music with a fade in effect. Will only resume if the
		 * sound has been paused.
		 * @param fadeIn Time the fade in effect will last (in seconds).
		 */
		void resume(double fadeIn);
		/**
		 * Destructor. Does not delete the sound data, only the sound source.
		 * This is done to be able to have many sounds playing the same
		 * sound without having it loaded many times in memory.
		 */
		virtual ~OpenSLAudio();
		/**
		 * Default constructor. Can only be called by the audio engine.
		 */
		OpenSLAudio();

		void setVolume(int newVolume);

	private:
		void soundEngineVolumeChanged();
		void musicEngineVolumeChanged();

		static void playCallback(SLPlayItf caller, void *pContext, SLuint32 event);

		void load(bool isMusic, OpenSLEngine* engine, const std::string &path, SLObjectItf engineObject, SLEngineItf engineEngine, SLObjectItf outputMixObject);
		int nbTimes;
		int nbRemainingTimes;
		std::string path;
		bool isMusic;

		OpenSLEngine* engine;
		SLObjectItf engineObject;
		SLEngineItf engineEngine;

		SLObjectItf outputMixObject;
		SLObjectItf playerObject;
		SLPlayItf playerPlay;
		SLSeekItf playerSeek;
		SLMuteSoloItf playerMuteSolo;
		SLVolumeItf playerVolume;
		SLmillibel maxLvl;
	};
}

#endif
