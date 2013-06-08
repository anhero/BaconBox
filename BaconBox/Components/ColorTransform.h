#ifndef BB_COLOR_TRANSFORM_H
#define BB_COLOR_TRANSFORM_H

#include "BaconBox/Core/Component.h"
#include "BaconBox/Display/Color.h"
#include "BaconBox/ColorMatrix.h"

namespace BaconBox {
	/**
	 * The ColorTransform component determines the entity's color.
	 */
	class ColorTransform : public Component {
	public:
		BB_ID_HEADER;

		static int MESSAGE_COLOR_CHANGED;

		ColorTransform();
		void setColor(const Color &color);
		virtual void setAlphaMultiplier(float alpha) = 0;
		virtual void setColorMultiplier(float r, float g, float b, float a) = 0;
		virtual void setColorOffset(float r, float g, float b, float a) = 0;

		const Color &getColor();
		virtual ColorMatrix &getConcatColorMatrix() = 0;

	private:
		Color color;

	};

	class ColorTransformProxy : public ComponentProxy {
	public:
		ColorTransformProxy(Entity *entity);
		void setColor(const Color &color);
		void setAlphaMultiplier(float alpha);
		void setColorMultiplier(float r, float g, float b, float a = 1.0f);
		void setColorOffset(float r, float g, float b, float a);
		const Color &getColor();
		ColorMatrix &getConcatColorMatrix();
		ColorTransform *getColorTransform();
	protected:
		void setColorTransform(ColorTransform *colorTransform);

	};
}

#endif /* defined(BB_COLOR_TRANSFORM_H) */
