/**
 * @file
 */
#ifndef BB_TEXTURE_POINTER_H
#define BB_TEXTURE_POINTER_H

#include "BaconBox/ResourcePointer.h"
#include "BaconBox/ResourceManager.h"

namespace BaconBox {
	struct TextureInformation;
	typedef ResourcePointer<TextureInformation, &ResourceManager::getTexture> TexturePointer;
}

#endif // BB_TEXTURE_POINTER_H
