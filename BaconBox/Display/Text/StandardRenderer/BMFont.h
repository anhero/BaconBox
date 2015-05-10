/**
 * @file
 * @ingroup TextDisplay
 */
#ifndef BB_BMFONT_H
#define BB_BMFONT_H

#include "BaconBox/Display/Text/StandardRenderer/TextureFont.h"

namespace BaconBox {
	class BMFont : public TextureFont {
	public:
		BMFont();
		BMFont(const std::string &newName);
		int getKerning(Char32 leftUnicodeValue, Char32 rightUnicodeValue);
		/**
		 * Return the glyph specified by the unicode value.
		 * The size of the font should be set before calling
		 * this function.
		 */
		TextureGlyphInformation *getGlyphInformation(Char32 unicodeValue);
		/**
		 * Set the font pixel size.
		 */
		void setPixelSize(int pixelSize);
		/// Detects the format and loads the font from the file.
		void loadFontFile(const std::string &filename);
	protected:
		void loadFontFileFromXML(const std::string &filename);
		void loadFontFileFromTXT(const std::string &filename);
		void loadFontFileFromBIN(const std::string &filename);
	};
}

#endif
