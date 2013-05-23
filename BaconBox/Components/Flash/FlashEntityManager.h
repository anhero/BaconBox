#ifndef BB_FLASHENTITYMANAGER_H
#define BB_FLASHENTITYMANAGER_H


#include "BaconBox/Core/Component.h"
#include <AS3/AS3.h>
#include <AS3/AS3++.h>

namespace BaconBox {
	class FlashEntityManager : public Component {
	public:

		BB_ID_HEADER;
		
		FlashEntityManager();
				
		virtual ~FlashEntityManager();
		
		void add(Entity *newEntity);
		void remove(Entity *newEntity);

		AS3::local::var getMovieClip();
						
		
		virtual void receiveMessage(int senderID, int destID, int message, void *data);


	void setProperty(const std::string & propertyName, AS3::local::var arg);
	AS3::local::var getProperty(const std::string & propertyName);
	AS3::local::var callMethod(const std::string & functionName, int argCount, AS3::local::var *args);
	private:
	    AS3::local::var movieClipManager;

	};
}

#endif
