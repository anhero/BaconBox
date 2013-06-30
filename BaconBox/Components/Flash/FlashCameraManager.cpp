
#include "BaconBox/Components/Flash/FlashCameraManager.h"
#include "BaconBox/Core/Flash/FlashEngine.h"
#include "BaconBox/Helper/Flash/FlashHelper.h"

#include "BaconBox/Components/Transform.h"
#include "BaconBox/Components/ColorTransform.h"

namespace BaconBox {

	BB_ID_IMPL(FlashCameraManager);

	FlashCameraManager::FlashCameraManager() : Component(), flashManager(NULL) {
		stage = FlashEngine::getStage();
	}

	FlashCameraManager::~FlashCameraManager() {
	}

	void FlashCameraManager::setEntityManager(FlashEntityManager *fm) {
		flashManager = fm;
	}

	void FlashCameraManager::receiveMessage(int senderID, int destID, int message, void *data) {
		Component::receiveMessage(senderID, destID, message, data);

		if (senderID == Transform::ID) {
			if (message == Transform::MESSAGE_POSITION_CHANGED) {
				Vector2ChangedData *pos = (reinterpret_cast<Vector2ChangedData *>(data));
				flashManager->setProperty("x", AS3::local::internal::new_int(-pos->newValue.x));
				flashManager->setProperty("y", AS3::local::internal::new_int(-pos->newValue.y));

			} else if (message == Transform::MESSAGE_ROTATION_CHANGED) {
				ValueChangedData<float> *rotation = reinterpret_cast<ValueChangedData<float>*>(data);
				flashManager->setProperty("rotation", AS3::local::internal::new_Number(-rotation->newValue));

			} else if (message == Transform::MESSAGE_SCALE_CHANGED) {
				Vector2ChangedData *scale = (reinterpret_cast<Vector2ChangedData *>(data));
				flashManager->setProperty("scaleX", AS3::local::internal::new_Number(scale->newValue.x));
				flashManager->setProperty("scaleY", AS3::local::internal::new_Number(scale->newValue.y));
			}

		} else if (senderID == ColorTransform::ID) {
			if (message == ColorTransform::MESSAGE_COLOR_CHANGED) {
				unsigned int colorValue = reinterpret_cast<Color *>(data)->getRGB();
				FlashHelper::setProperty(stage, "color", AS3::local::internal::new_uint(colorValue));
			}
		}
	}
}