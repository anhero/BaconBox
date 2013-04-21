/**
 * @file
 * @ingroup Audio
 */
#ifndef BB_OPENAL_H
#define BB_OPENAL_H

#include "BaconBox/PlatformFlagger.h"

#ifdef BB_OPENAL

#ifdef BB_WIN32
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

#endif
