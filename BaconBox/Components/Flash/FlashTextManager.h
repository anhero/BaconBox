#ifndef BB_FLASHTEXTMANAGER_H
#define BB_FLASHTEXTMANAGER_H


#include "../../Core/Component.h"
#include "BaconBox/Display/Text/TextAlignment.h"
#include <AS3/AS3.h>
#include <AS3/AS3++.h>
#include "BaconBox/Display/Color.h"

namespace BaconBox {
	
	class MovieClipHolder;
	class FlashTextManager : public Component {
	public:
		BB_ID_HEADER;

		FlashTextManager();
		
		virtual ~FlashTextManager();

		void initializeConnections();
		void setText(const std::string &text);
		void setColor(const Color &newColor);
		void setAlignment(TextAlignment::type alignment);

		virtual void receiveMessage(int senderID, int destID, int message, void *data);

	private:
		MovieClipHolder * movieClipHolder;
		Color color;
			AS3::local::var textField;

	};

}

#endif
