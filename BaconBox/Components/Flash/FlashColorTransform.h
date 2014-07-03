#ifndef BB_FLASH_COLOR_TRANSFORM_H
#define BB_FLASH_COLOR_TRANSFORM_H

#include "BaconBox/Core/Component.h"
#include "BaconBox/Display/Color.h"

#include "BaconBox/Components/Flash/MovieClipHolder.h"

#include "BaconBox/Components/ColorTransform.h"
#include "BaconBox/ColorMatrix.h"
#include "BaconBox/Components/EntityContainer.h"


namespace BaconBox {
	class FlashColorTransform : public ColorTransform {
	public:

		FlashColorTransform();
		ColorMatrix & getMatrix();
		ColorMatrix & getConcatColorMatrix();

		void setAlphaMultiplier(float alpha);
		void setColorMultiplier(float r, float g, float b, float a);
		void setColorOffset(float r, float g, float b, float a);
    	protected:

	private:
		ColorMatrix matrix;
		MovieClipHolder * movieClipHolder;
		void initializeConnections();
	};

}

#endif /* defined(BB_FLASH_COLOR_TRANSFORM_H) */
