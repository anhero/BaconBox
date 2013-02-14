/**
 * @file
 * @ingroup Display
 */
#ifndef BB_FONTFORMAT_H
#define BB_FONTFORMAT_H

#include "BaconBox/Helper/SafeEnum.h"

namespace BaconBox {

	/**
	 * Enum type representing the color component format.
	 * Used internally to interpret buffers values.
	 * @ingroup Display
	 */
	struct FontFormatDef {
		enum type {
		    NONE,
		    BMFONT
		};
	};
	typedef SafeEnum<FontFormatDef> FontFormat;
}

#endif
