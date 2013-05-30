/**
 * @file
 * @ingroup Display
 */
#ifndef BB_COLORFORMAT_H
#define BB_COLORFORMAT_H

#include "BaconBox/Helper/SafeEnum.h"

namespace BaconBox {

	/**
	 * Enum type representing the color component format.
	 * Used internally to interpret buffers values.
	 * @ingroup Display
	 */
	struct ColorFormatDef {
		enum type {
			NONE,
			RGBA,
			ALPHA
		};
	};
	typedef SafeEnum<ColorFormatDef> ColorFormat;
}

#endif
