/**
 * @file
 * @ingroup Display
 */
#ifndef BB_SUB_TEXTURE_INFO_H
#define BB_SUB_TEXTURE_INFO_H

#include "BaconBox/Display/TextureInformation.h"
#include "BaconBox/Vector2.h"


namespace BaconBox {

	struct SubTextureInfo {
		SubTextureInfo(TextureInformation * textureInfo = NULL, Vector2 position = Vector2(), Vector2 size = Vector2());
		Vector2 position;
		Vector2 size;
		TextureInformation * textureInfo;
	};
}
#endif
