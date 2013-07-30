#ifndef BB_FLASH_SIZECOMPONENT_H
#define BB_FLASH_SIZECOMPONENT_H
#include "BaconBox/Components/SizeComponent.h"
#include "BaconBox/Components/Flash/MovieClipHolder.h"
#include "BaconBox/Components/ComponentConnection.h"
namespace BaconBox {

	class FlashSizeComponent : public SizeComponent {
	public:
		FlashSizeComponent();

		float getWidth() const;
		float getHeight() const;
	protected:
	private:
		MovieClipHolder *movieClipHolder;
		void initializeConnections();
	};
}

#endif // BB_FLASH_SIZECOMPONENT_H
