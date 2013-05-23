#ifndef BB_DEFAULT_COLOR_TRANSFORM_H
#define BB_DEFAULT_COLOR_TRANSFORM_H

#include "BaconBox/Core/Component.h"
#include "BaconBox/Display/Color.h"

#include "BaconBox/Components/ColorTransform.h"
#include "BaconBox/ColorMatrix.h"
#include "BaconBox/Components/EntityContainer.h"


namespace BaconBox {
    class EntityFactory;
	class DefaultColorTransform : public ColorTransform {
	    friend class EntityFactory;
	public:

		DefaultColorTransform();

		void setAlphaMultiplier(float alpha);
		void setColorMultiplier(float r, float g, float b, float a);
		void setColorOffset(float r, float g, float b, float a);
		ColorMatrix & getConcatColorMatrix();
        void setFrameColorTransform(int frame);
    	protected:
		void initializeConnections();

	private:
	    bool useCustomMatrix;
		ColorMatrix matrix;
		ColorMatrix concatMatrix;
		EntityContainer * entityContainer;
        std::map<int, ColorMatrix> matrixByParentFrame;

	};

}

#endif /* defined(BB_DEFAULT_COLOR_TRANSFORM_H) */
