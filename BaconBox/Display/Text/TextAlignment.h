/**
 * @file
 * @ingroup TextDisplay
 */
#ifndef BB_TEXT_ALIGNMENT_H
#define BB_TEXT_ALIGNMENT_H

#include "BaconBox/Helper/SafeEnum.h"

namespace BaconBox {
	struct TextAlignment {
		enum type {
			LEFT,
			RIGHT,
			CENTER
		};
			
	private:
	    TextAlignment();
	};

}

#endif
