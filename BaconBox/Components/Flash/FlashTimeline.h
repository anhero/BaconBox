#ifndef BB_FLASH_TIMELINE_H
#define BB_FLASH_TIMELINE_H

#include "BaconBox/Core/Component.h"
#include "BaconBox/Components/Timeline.h"
#include "MovieClipHolder.h"
namespace BaconBox {
	class FlashTimeline : public Timeline {
	public:
		
		
		FlashTimeline();
		
		FlashTimeline(const FlashTimeline &src);
		
		~FlashTimeline();
		
		void receiveMessage(int senderID, int destID, int message, void *data);
		
		void gotoAndPlay(int frame);

		void gotoAndPlay(const std::string &labelName);
		
		void gotoAndStop(int frame);

		void gotoAndStop(const std::string &labelName);

		void nextFrame();
		
		void prevFrame();
		
		void play();
		
		void stop();
		
		int getCurrentFrame() const;
		
		bool isPlaying() const;
		
		int getNbFrames() const;

		bool hasLabel(const std::string& label) const;

	private:
		MovieClipHolder * movieClipHolder;
		void initializeConnections();

	};
	
}

#endif /* defined(BB_FLASH_TIMELINE_H) */

