#ifndef BB_RENDER_MODE_H
#define BB_RENDER_MODE_H

namespace BaconBox {
	namespace RenderMode {
		const int NONE = 0;
		const int SHAPE = 1;
		const int TEXTURE = 2;
		const int COLOR = 4;
		const int MASKED = 8;
		const int INVERSE_MASKED = 16;
		const int COLOR_TRANSORMED = 32;
		const int BLENDED = 64;
	};
}

#endif
