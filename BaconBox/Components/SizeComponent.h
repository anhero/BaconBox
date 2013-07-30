#ifndef BB_SIZECOMPONENT_H
#define BB_SIZECOMPONENT_H

#include "BaconBox/Core/Component.h"
#include "BaconBox/Vector2.h"
#include "BaconBox/Core/Entity.h"

namespace BaconBox {
	/**
	 * The SizeComponent determines the width and height of an entity.
	 */
	class SizeComponent : public Component {
	public:
		BB_ID_HEADER;
		SizeComponent();
		SizeComponent(const SizeComponent &src);
		SizeComponent &operator=(const SizeComponent &src);
		virtual float getWidth() const = 0;
		virtual float getHeight() const = 0;
		virtual const Vector2 getSize() const;
	};

	class SizeComponentProxy : public ComponentProxy {
	public:
		SizeComponentProxy(Entity *entity);
		float getWidth() const;
		float getHeight() const;
		const Vector2 getSize() const;

	protected:
		void setSizeComponent(SizeComponent *sizeComponent);

	};
}

#endif // BB_SIZECOMPONENT_H
