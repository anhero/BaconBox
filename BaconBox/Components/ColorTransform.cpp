#include "ColorTransform.h"

#include "BaconBox/Core/IDManager.h"
#include "BaconBox/Core/Entity.h"
#include "BaconBox/Console.h"
namespace BaconBox {
	
	BB_ID_IMPL(ColorTransform);

	int ColorTransform::MESSAGE_COLOR_CHANGED = IDManager::generateID();

	ColorTransform::ColorTransform() : Component(), color(Color::WHITE) {
	}

	void ColorTransform::setColor(const Color &newColor) {
		color = newColor;
		sendMessage(Entity::BROADCAST, MESSAGE_COLOR_CHANGED, &(this->color));
	}
	
	const Color &ColorTransform::getColor() {
		return color;
	}

	ColorTransformProxy::ColorTransformProxy(Entity *entity): ComponentProxy(entity, NULL), alpha(this, &ColorTransformProxy::getAlpha, &ColorTransformProxy::setAlpha)  {
	}
	float ColorTransformProxy::getAlpha() const {
		return reinterpret_cast<ColorTransform *>(component)->getMatrix().colorMultiplier.getAlpha();
	}
	
	void ColorTransformProxy::setAlpha(float alpha) {
		reinterpret_cast<ColorTransform *>(component)->setAlphaMultiplier(alpha);
	}
	
	ColorMatrix   &ColorTransformProxy::getConcatColorMatrix() {
		return reinterpret_cast<ColorTransform *>(component)->getConcatColorMatrix();
	}

	void ColorTransformProxy::setColor(const Color &color) {
		reinterpret_cast<ColorTransform *>(component)->setColor(color);
	}

	void ColorTransformProxy::setAlphaMultiplier(float alpha) {
		reinterpret_cast<ColorTransform *>(component)->setAlphaMultiplier(alpha);
	}

	void ColorTransformProxy::setColorMultiplier(float r, float g, float b, float a) {
		reinterpret_cast<ColorTransform *>(component)->setColorMultiplier(r, g, b, a);
	}
	void ColorTransformProxy::setColorOffset(float r, float g, float b, float a) {
		reinterpret_cast<ColorTransform *>(component)->setColorOffset(r, g, b, a);
	}
	const Color &ColorTransformProxy::getColor() {
		return  reinterpret_cast<ColorTransform *>(component)->getColor();
	}

	ColorTransform *ColorTransformProxy::getColorTransform() {
		return reinterpret_cast<ColorTransform *>(component);
	}
	void ColorTransformProxy::setColorTransform(ColorTransform *colorTransform) {
		component = colorTransform;
		entity->addComponent(component);
	}

}
