#ifndef BB_DEFAULT_COLOR_TRANSFORM_H
#define BB_DEFAULT_COLOR_TRANSFORM_H

#include "BaconBox/Core/Component.h"
#include "BaconBox/Display/Color.h"

#include "BaconBox/Components/ColorTransform.h"
#include "BaconBox/ColorMatrix.h"
#include "BaconBox/Components/EntityContainer.h"

namespace BaconBox {

	class DefaultColorTransform : public ColorTransform {
	public:

		DefaultColorTransform();
		void setAlpha(uint8_t alpha);
		Color & getConcatColor();
		ColorMatrix & getConcatColorMatrix();

	protected:
		void initializeConnections();

	private:
		ColorMatrix matrix;
		ColorMatrix concatMatrix;

		Color color;
		EntityContainer * entityContainer;
	};

}

#endif /* defined(BB_DEFAULT_COLOR_TRANSFORM_H) */
