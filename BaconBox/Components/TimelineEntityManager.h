#ifndef BB_TIMELINE_ENTITY_MANAGER_H
#define BB_TIMELINE_ENTITY_MANAGER_H

#include <utility>
#include <vector>
#include <string>

#include "BaconBox/Core/Component.h"

namespace BaconBox {
	class TimelineEntityManager : public Component {
	public:
		BB_ID_HEADER;
		
		TimelineEntityManager();
		
		TimelineEntityManager(const TimelineEntityManager &src);
		
		virtual ~TimelineEntityManager();
		
		TimelineEntityManager &operator=(const TimelineEntityManager &src);
		
		virtual void receiveMessage(int senderID, int destID, int message, void *data);
		
		virtual void gotoAndPlay(int frame) = 0;
		
		virtual void gotoAndStop(int frame) = 0;
		
		virtual void nextFrame() = 0;
		
		virtual void prevFrame() = 0;
		
		virtual void play() = 0;
		
		virtual void stop() = 0;
		
		virtual int getCurrentFrame() const = 0;
		
		virtual int getNbFramesLoaded() const = 0;
		
		virtual bool isPlaying() const = 0;
		
		virtual int getNbTotalFrames() const = 0;
	};
}

#endif /* defined(BB_TIMELINE_ENTITY_MANAGER_H) */

