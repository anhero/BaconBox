#ifndef BB_FLASHENTITYMANAGER_H
#define BB_FLASHENTITYMANAGER_H


#include "BaconBox/Core/Component.h"
#include <AS3/AS3.h>
#include <AS3/AS3++.h>

namespace BaconBox {
	class FlashEntityManager : public Component {
	public:
		static int ID;
		
		FlashEntityManager();
				
		virtual ~FlashEntityManager();
		
		void add(Entity *newEntity);
		void remove(Entity *newEntity);

		AS3::local::var getMovieCLip();
						
		virtual int getID() const;
		
		virtual void receiveMessage(int senderID, int destID, int message, void *data);

	private:
	    AS3::local::var movieClipManager;

	};
}

#endif
