#ifndef BB_FLASH_TRANSFORM_H
#define BB_FLASH_TRANSFORM_H

#include "BaconBox/Components/Transform.h"
#include "BaconBox/Components/Flash/MovieClipHolder.h"
#include "BaconBox/Components/ComponentConnection.h"

namespace BaconBox {

	class FlashTransform : public Transform {
	public:

		FlashTransform();
		const Vector2 &getRealPosition() const;
	private:
		void initializeConnections();
		MovieClipHolder * movieClipHolder;
		Vector2 realPosition;

	};

}

#endif
