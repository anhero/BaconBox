/**
 * @file
 * @ingroup TextDisplay
 */
#ifndef BB_FONT_H
#define BB_FONT_H

#include <string>
#include "BaconBox/Display/Text/TextureGlyphInformation.h"
#include "BaconBox/Helper/String32.h"

namespace BaconBox {

	class Font {
	public:
		Font();
		Font(const std::string &newName);
		/**
		 * Return the name of the font.
		 */
		const std::string &getName() const;
		
		void setName(const std::string &newName);
		

		/**
		 * Set the font pixel size.
		 */
		virtual void setPixelSize(int pixelSize);
		int getPixelSize();


	protected:
	    std::string name;
	    int pixelSize;
	};
}

#endif
