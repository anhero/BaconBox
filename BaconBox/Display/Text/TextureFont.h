/**
 * @file
 * @ingroup TextDisplay
 */
#ifndef BB_TEXTURE_FONT_H
#define BB_TEXTURE_FONT_H

#include "BaconBox/Display/Text/Font.h"

namespace BaconBox {

	class TextureFont : public Font{
	public:
		TextureFont();
		TextureFont(const std::string &newName);

				
		virtual int getKerning(Char32 leftUnicodeValue, Char32 rightUnicodeValue) = 0;
		
		/**
		 * Return the glyph specified by the unicode value.
		 * The size of the font should be set before calling
		 * this function.
		 */
		virtual TextureGlyphInformation *getGlyphInformation(Char32 unicodeValue) =0;

		int getLineHeight();
		int getPixelSize();
	protected:
		std::map<std::pair<Char32, Char32>, int> kerningMap;
		std::map<int, TextureGlyphInformation*> charsMap;
		int pixelSize;
		int lineHeight;
	};
}

#endif
