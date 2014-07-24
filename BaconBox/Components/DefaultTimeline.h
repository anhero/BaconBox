#ifndef BB_DEFAULT_TIMELINE_H
#define BB_DEFAULT_TIMELINE_H

#include "BaconBox/Components/Timeline.h"
#include "BaconBox/Components/MatrixComponent.h"
#include "BaconBox/Components/SymbolComponent.h"



namespace BaconBox {
	class DefaultEntityContainer;
	class DefaultTimeline : public Timeline {
	public:
		DefaultTimeline();

		DefaultTimeline(const DefaultTimeline &src);

		virtual ~DefaultTimeline();

		DefaultTimeline &operator=(const DefaultTimeline &src);

		DefaultTimeline *clone() const;

		void receiveMessage(int senderID, int destID, int message, void *data);

		void update();

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

		void setNbFrames(int newNbFrames);

		bool hasLabel(const std::string& label) const;

	private:

	    SymbolComponent * symbolComponent;

	    int endFrame;

		 void setFrame(int frame);
		void gotoAndSetState(int frame, bool newPlaying);

		void gotoAndSetState(const std::string &newName, bool newPlaying);

		void initializeConnections();

		bool playing;

		int nbFrames;

		int currentFrame;
		DefaultEntityContainer * defaultEntityContainer;


	};


}

#endif /* defined(BB_DEFAULT_TIMELINE_H) */

