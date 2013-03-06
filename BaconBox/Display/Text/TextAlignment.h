/**
 * @file
 * @ingroup TextDisplay
 */
#ifndef RB_TEXT_ALIGNMENT_H
#define RB_TEXT_ALIGNMENT_H

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
