/**
 * @file
 * @ingroup Audio
 */
 
#ifndef BB_SOUND_INFO_H
#define BB_SOUND_INFO_H

#include "BaconBox/PlatformFlagger.h"

#ifdef BB_OPENAL
#ifdef BB_WINDOWS_PLATFORM
#include <al.h>
#include <alc.h>
#elif defined(BB_LINUX)
#include <AL/al.h>
#include <AL/alc.h>
#elif defined(BB_APPLE_PLATFORM)
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#endif
#endif

#ifdef BB_SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#endif

#include <string>

namespace BaconBox {
	/**
	 * Contains the data about a sound that can be played.
	 * @ingroup Audio
	 */
	struct SoundInfo {
#ifdef BB_OPENAL
		/// OpenAL sound buffer ID.
		ALuint bufferId;
#endif
#ifdef BB_SDL
		/// Pointer to SDL's sound data.
		Mix_Chunk* data;
#endif
	};
}
 
#endif
