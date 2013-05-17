#ifndef BB_COLOR_TRANSFORM_H
#define BB_COLOR_TRANSFORM_H

#include "BaconBox/Core/Component.h"
#include "BaconBox/Display/Color.h"
#include "BaconBox/ColorMatrix.h"

namespace BaconBox {

	class ColorTransform : public Component {
	public:
		BB_ID_HEADER;

		ColorTransform();
		virtual void setAlpha(uint8_t alpha) = 0;
		virtual ColorMatrix & getConcatColorMatrix() = 0;

	private:

	};

	class ColorTransformProxy : public ComponentProxy {
	public:
		ColorTransformProxy(Entity *entity);

		void setAlpha(uint8_t alpha);
		ColorMatrix & getConcatColorMatrix();
	protected:
	    void setColorTransform(ColorTransform * colorTransform);

	};
}

#endif /* defined(BB_COLOR_TRANSFORM_H) */
