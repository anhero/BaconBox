#include "BaconBox/Display/Text/TextureGlyphInformation.h"

namespace BaconBox {
	TextureGlyphInformation::TextureGlyphInformation() : advance(), offset(), charCode(-1), subTextureInfo(NULL) {
	}

	TextureGlyphInformation::TextureGlyphInformation(const Vector2 &newAdvance,
	                                   const Vector2 &newOffset,
					   Char32 charCode,
	                                   SubTextureInfo *newsubTextureInfo) :
		advance(newAdvance), offset(newOffset), charCode(charCode), subTextureInfo(newsubTextureInfo) {
	}

	TextureGlyphInformation::TextureGlyphInformation(const TextureGlyphInformation &src) :
		advance(src.advance), offset(src.offset), charCode(src.charCode), subTextureInfo(src.subTextureInfo) {
	}

	TextureGlyphInformation &TextureGlyphInformation::operator=(const TextureGlyphInformation &src) {
		if (this != &src) {
			advance = src.advance;
			offset = src.offset;
			charCode = src.charCode;
			subTextureInfo = src.subTextureInfo;
		}

		return *this;
	}
}
