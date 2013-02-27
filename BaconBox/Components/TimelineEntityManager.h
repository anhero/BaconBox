#ifndef BB_TIMELINE_ENTITY_MANAGER_H
#define BB_TIMELINE_ENTITY_MANAGER_H

#include <utility>
#include <vector>
#include <string>

#include "BaconBox/Core/Component.h"
#include "BaconBox/Vector2.h"

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
		
		virtual Entity *addChild(Entity *newChild) = 0;
		
		virtual Entity *addChildAt(Entity *newChild, int index) = 0;
		
		virtual bool contains(Entity *child) const = 0;

		virtual Entity *getChildAt(int index) = 0;
		
		virtual const Entity *getChildAt(int index) const = 0;
		
		virtual Entity *getChildByName(const std::string &name) = 0;
		
		virtual const Entity *getChildByName(const std::string &name) const = 0;
		
		virtual int getChildIndex(Entity *child) const = 0;
		
		virtual std::vector<Entity *> getObjectsUnderPoint(const Vector2 &point) const = 0;
		
		virtual Entity *removeChild(Entity *child) = 0;
		
		virtual Entity *removeChildAt(int index) = 0;
		
		virtual Entity *removeChildren(int beginIndex, int endIndex) = 0;
		
		virtual void setChildIndex(Entity *child, int index) = 0;
		
		virtual void swapChildren(Entity *child1, Entity *child2) = 0;
		
		virtual void swapChildrenAt(int index1, int index2) = 0;
		
		virtual int getNbChildren() const = 0;
	};
}

#endif /* defined(BB_TIMELINE_ENTITY_MANAGER_H) */

