#ifndef BB_FLASH_TIMELINE_H
#define BB_FLASH_TIMELINE_H

#include "BaconBox/Core/Component.h"
#include "BaconBox/Components/Timeline.h"
namespace BaconBox {
	class FlashTimeline : public Timeline {
	public:
		
		
		FlashTimeline();
		
		FlashTimeline(const FlashTimeline &src);
		
		~FlashTimeline();
		
		void receiveMessage(int senderID, int destID, int message, void *data);
		
		void gotoAndPlay(int frame);
		
		void gotoAndStop(int frame);
		
		void nextFrame();
		
		void prevFrame();
		
		void play();
		
		void stop();
		
		int getCurrentFrame() const;
		
		bool isPlaying() const;
		
		int getNbFrames() const;
	};
	
}

#endif /* defined(BB_FLASH_TIMELINE_H) */

