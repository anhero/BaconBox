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

		virtual void gotoAndPlay(const std::string &newName) = 0;

		virtual void gotoAndStop(int frame) = 0;

        virtual void gotoAndStop(const std::string &newName) = 0;

		virtual void nextFrame() = 0;

		virtual void prevFrame() = 0;

		virtual void play() = 0;

		virtual void stop() = 0;

		virtual int getCurrentFrame() const = 0;

		virtual bool isPlaying() const = 0;

		virtual int getNbFrames() const = 0;
	};


	class TimelineProxy : public ComponentProxy {
	public:
		TimelineProxy(Entity *entity);

		void gotoAndPlay(int frame);

		void gotoAndPlay(const std::string &newName);

		void gotoAndStop(int frame);

        void gotoAndStop(const std::string &newName);

		void nextFrame();

		void prevFrame();

		void play();

		void stop();

		int getCurrentFrame() const;

		bool isPlaying() const;

		int getNbFrames() const;

	protected:
	    void setTimeline(Timeline * timeline);
	};
}

#endif /* defined(BB_TIMELINE_H) */

