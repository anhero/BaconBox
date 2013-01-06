#ifndef BB_WINDOW_ORIENTATION
#define BB_WINDOW_ORIENTATION

#include "BaconBox/Helper/SafeEnum.h"

namespace BaconBox {
	struct WindowOrientationDef {
		enum type {
			NORMAL,
			UPSIDE_DOWN,
			HORIZONTAL_LEFT,
			HORIZONTAL_RIGHT
		};
	};
	
	typedef SafeEnum<WindowOrientationDef> WindowOrientation;
}

#endif
