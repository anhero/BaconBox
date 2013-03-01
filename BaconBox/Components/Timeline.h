#ifndef BB_TIMELINE_H
#define BB_TIMELINE_H

#include "BaconBox/Core/Component.h"

namespace BaconBox {
	/**
	 * Base class for components that manage the animations and its frames.
	 */
	class Timeline : public Component {
	public:
		BB_ID_HEADER;
		
		static int MESSAGE_NB_FRAMES_CHANGED;
		
		Timeline();
		
		Timeline(const Timeline &src);
		
		virtual ~Timeline();
		
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

#endif /* defined(BB_TIMELINE_H) */

