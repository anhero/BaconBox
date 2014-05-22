/**
 * @file
 * @ingroup Audio
 */
#ifndef BB_MUSIC_INFO_H
#define BB_MUSIC_INFO_H

#include "BaconBox/PlatformFlagger.h"

#if defined(BB_AV_AUDIO_PLAYER) || defined(BB_ANDROID)
#include <string>
#endif

#ifdef BB_SDL
#include <SDL2/SDL_mixer.h>
//#include <SDL/SDL_mixer.h>

#endif

#ifdef BB_FLASH_PLATFORM
#include <AS3/AS3.h>
#include <AS3/AS3++.h>
#endif

namespace BaconBox {
	/**
	 * Contains the data about a sound that can be played. Contains platform-
	 * specific data. They must use preprocessors command to set its members.
	 * @ingroup Audio
	 */
	struct MusicInfo {
#if defined(BB_AV_AUDIO_PLAYER) || defined(BB_ANDROID)
		/// Path to the music file.
		std::string filePath;
#endif
#ifdef BB_SDL
		Mix_Music* music;
#endif
		
#ifdef BB_FLASH_PLATFORM
AS3::local::var sound;
#endif
	};
}
 
 #endif
