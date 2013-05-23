#ifndef BB_FLASHCAMERAMANAGER_H
#define BB_FLASHCAMERAMANAGER_H

#include "BaconBox/Components/Flash/FlashEntityManager.h"
#include "BaconBox/Core/Component.h"
#include <AS3/AS3.h>
#include <AS3/AS3++.h>

namespace BaconBox {
	class FlashCameraManager : public Component {
	public:

		BB_ID_HEADER;
		
		FlashCameraManager();
		void setEntityManager(FlashEntityManager *fm);	
		virtual ~FlashCameraManager();
		void receiveMessage(int senderID, int destID, int message, void *data);


	private:
	    FlashEntityManager *flashManager;
	    AS3::local::var stage;

	};
}

#endif
