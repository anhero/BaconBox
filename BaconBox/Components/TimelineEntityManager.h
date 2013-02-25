#ifndef BB_TIMELINE_ENTITY_MANAGER_H
#define BB_TIMELINE_ENTITY_MANAGER_H

#include "BaconBox/Core/Component.h"

namespace BaconBox {
	class TimelineEntityManager : public Component {
	public:
		TimelineEntityManager();
		
		TimelineEntityManager(const TimelineEntityManager &src);
		
		virtual ~TimelineEntityManager();
		
		TimelineEntityManager &operator=(const TimelineEntityManager &src);
		
		virtual TimelineEntityManager *clone() const;
		
		virtual void receiveMessage(int senderID, int destID, int message, void *data);
	private:
	};
}

#endif /* defined(BB_TIMELINE_ENTITY_MANAGER_H) */

