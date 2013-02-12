#include "BaconBox/Display/Text/TextureGlyphInformation.h"

namespace BaconBox {
	TextureGlyphInformation::TextureGlyphInformation() : advance(), horizontalBearing(),
		size(), textureInformation(NULL) {
	}

	TextureGlyphInformation::TextureGlyphInformation(const Vector2 &newAdvance,
	                                   const Vector2 &newHorizontalBearing,
	                                   const Vector2 &newSize,
	                                   TextureInformation *newTextureInformation) :
		advance(newAdvance), horizontalBearing(newHorizontalBearing),
		size(newSize), textureInformation(newTextureInformation) {
	}

	TextureGlyphInformation::TextureGlyphInformation(const TextureGlyphInformation &src) :
		advance(src.advance), horizontalBearing(src.horizontalBearing),
		size(src.size), textureInformation(src.textureInformation) {
	}

	TextureGlyphInformation &TextureGlyphInformation::operator=(const TextureGlyphInformation &src) {
		if (this != &src) {
			advance = src.advance;
			horizontalBearing = src.horizontalBearing;
			size = src.size;
			textureInformation = src.textureInformation;
		}

		return *this;
	}
}
