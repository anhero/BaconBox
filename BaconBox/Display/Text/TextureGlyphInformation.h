/**
 * @file
 * @ingroup TextDisplay
 */
#ifndef BB_GLYPH_INFORMATION_H
#define BB_GLYPH_INFORMATION_H

#include "BaconBox/Vector2.h"
#include "BaconBox/Display/SubTextureInfo.h"

namespace BaconBox {
	/**
	 * This struct contain the needed informations to render a glyph.
	 * @ingroup TextDisplay
	 */
	struct TextureInformation;
	struct TextureGlyphInformation {
	public:
		/**
		 * Amount of pixels we need to add to the current horizontal and
		 * vertical position before rendering the next character. The horizontal
		 * advance is the amount of pixels we need to add to the "pen" position
		 * before rendering the next glyph when we are drawing in horizontal
		 * layout.
		 */
		Vector2 advance;

		Vector2 offset;


		/// Pointer to the texture handle and texture size.
		SubTextureInfo *subTextureInfo;

		/**
		 * Default constructor.
		 */
		TextureGlyphInformation();

		/**
		 * Parameterized constructor.
		 * @param newAdvance Advance of the glyph.
		 * @param newHorizontalBearing Horizontal bearing.
		 * @param newSize Size of the glyph.
		 * @param newTextureInformation Pointer to the glyph's texture
		 * information.
		 */
		TextureGlyphInformation(const Vector2 &newAdvance,
		                 const Vector2 &newOffset,
		                 SubTextureInfo  *newsubTextureInfo);

		/**
		 * Copy constructor.
		 * @param src GlyphInformation to make a copy of.
		 */
		TextureGlyphInformation(const TextureGlyphInformation &src);

		/**
		 * Assignment operator.
		 * @param src GlyphInformation to make a copy of.
		 * @return Reference to the modified GlyphInformation.
		 */
		TextureGlyphInformation &operator=(const TextureGlyphInformation &src);
	};

}

#endif // BB_GLYPH_INFORMATION_H
