/**
 * @file
 * @ingroup Audio
 */
#ifndef BB_SOUND_PARAMETERS_H
#define BB_SOUND_PARAMETERS_H

#include <string>

#include "BaconBox/PlatformFlagger.h"

namespace BaconBox {
	struct SoundParameters {
		/// Name used by the ResourceManager.
		std::string name;
#if defined(BB_OPENAL) || defined(BB_SDL)|| defined(BB_ANDROID)
		std::string path;
#endif
	};
}

#endif
