/**
 * @file
 * @ingroup Audio
 */
#ifndef BB_MUSIC_INFO_H
#define BB_MUSIC_INFO_H

#include "BaconBox/PlatformFlagger.h"

#ifdef BB_AV_AUDIO_PLAYER
#include <string>
#endif

#ifdef BB_SDL
#include <SDL2/SDL_mixer.h>
//#include <SDL/SDL_mixer.h>

#endif

namespace BaconBox {
	/**
	 * Contains the data about a sound that can be played. Contains platform-
	 * specific data. They must use preprocessors command to set its members.
	 * @ingroup Audio
	 */
	struct MusicInfo {
#ifdef BB_AV_AUDIO_PLAYER
		/// Path to the music file.
		std::string filePath;
#endif
#ifdef BB_SDL
		Mix_Music* music;
#endif
	};
}
 
 #endif
