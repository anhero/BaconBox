#ifndef BB_DefaultTimelineEntityManager_H
#define BB_DefaultTimelineEntityManager_H

#include "BaconBox/Components/TimelineEntityManager.h"
#include "BaconBox/Helper/Range.h"

namespace BaconBox {
	class DefaultTimelineEntityManager : public TimelineEntityManager {
	public:
		DefaultTimelineEntityManager();
		
		DefaultTimelineEntityManager(const DefaultTimelineEntityManager &src);
		
		~DefaultTimelineEntityManager();
		
		DefaultTimelineEntityManager &operator=(const DefaultTimelineEntityManager &src);
		
		DefaultTimelineEntityManager *clone() const;
		
		void receiveMessage(int senderID, int destID, int message, void *data);
		
		void update();
		
		void render();
		
		void gotoAndPlay(int frame);
		
		void gotoAndStop(int frame);
		
		void nextFrame();
		
		void prevFrame();
		
		void nextScene();
		
		void prevScene();
		
		void play();
		
		void stop();
		
		int getCurrentFrame() const;
		
		std::string getCurrentFrameLabel() const;
		
		std::string getCurrentLabel() const;
		
		std::vector<std::pair<std::string, int> > getCurrentLabels() const;
		
		Scene getCurrentScene() const;
		
		SceneArray getScenes() const;
		
		int getNbFramesLoaded() const;
		
		bool isPlaying() const;
		
		int getNbTotalFrames() const;
	private:
		typedef std::map<std::string, std::map<Range<int>, Entity *, Range<int>::Comparator > > ChildMap;
		
		ChildMap children;
		
		SceneArray scenes;
		SceneArray::size_type currentScene;
		
		bool playing;
		
		int nbTotalFrames;
	};
}

#endif /* defined(BB_DefaultTimelineEntityManager_H) */

