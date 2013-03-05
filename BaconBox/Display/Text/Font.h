/**
 * @file
 * @ingroup TextDisplay
 */
#ifndef BB_FONT_H
#define BB_FONT_H

#include <string>
#include "BaconBox/Display/Text/TextEntity.h"
#include "BaconBox/Display/Text/TextureGlyphInformation.h"
#include "BaconBox/Helper/String32.h"
#include "FontFormat.h"

namespace BaconBox {
    class TextEntity;
	class Font {
	    friend class ResourceManager;
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
		
		virtual TextEntity * getTextEntity();
		
		FontFormat getFormat();

	protected:
	    FontFormat format;
	    std::string name;
	    int pixelSize;
	};
}

#endif
