#include "BaconBox/Display/Text/TextureGlyphInformation.h"

namespace BaconBox {
	TextureGlyphInformation::TextureGlyphInformation() : advance(), offset(), subTextureInfo(NULL) {
	}

	TextureGlyphInformation::TextureGlyphInformation(const Vector2 &newAdvance,
	                                   const Vector2 &newOffset,
	                                   SubTextureInfo *newsubTextureInfo) :
		advance(newAdvance), offset(newOffset), subTextureInfo(newsubTextureInfo) {
	}

	TextureGlyphInformation::TextureGlyphInformation(const TextureGlyphInformation &src) :
		advance(src.advance), offset(src.offset),subTextureInfo(src.subTextureInfo) {
	}

	TextureGlyphInformation &TextureGlyphInformation::operator=(const TextureGlyphInformation &src) {
		if (this != &src) {
			advance = src.advance;
			offset = src.offset;
			subTextureInfo = src.subTextureInfo;
		}

		return *this;
	}
}
