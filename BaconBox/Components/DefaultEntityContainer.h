#ifndef BB_DEFAULT_ENTITY_CONTAINER_H
#define BB_DEFAULT_ENTITY_CONTAINER_H

#include <vector>
#include <map>
#include <string>
#include <deque>
#include "BaconBox/Components/EntityContainer.h"
#include "BaconBox/Helper/Range.h"
#include "BaconBox/Helper/ValueChangedData.h"
#include "DefaultTimeline.h"

namespace BaconBox {
	class Timeline;
	class Visibility;
	class EntityContainerLooper;

	class DefaultEntityContainer : public EntityContainer {
		friend class EntityContainerLooper;
	public:
		typedef std::map<int, std::deque<MovieClipEntity*> > ChildArray;

		DefaultEntityContainer();

//		DefaultEntityContainer(const DefaultEntityContainer &src);

		virtual ~DefaultEntityContainer();

//		DefaultEntityContainer &operator=(const DefaultEntityContainer &src);
//
//		DefaultEntityContainer *clone() const;

		void receiveMessage(int senderID, int destID, int message, void *data);



		void update();


		void propagateMessage(int senderID, int destID, int message, void *data);


		void addChild(MovieClipEntity *newChild);

		void addChildToCurrentFrame(MovieClipEntity *newChild);


		void addChild(MovieClipEntity *newChild, int frame);

		void addChildAt(MovieClipEntity *newChild, int index);

		void addChildAt(MovieClipEntity *newChild, int index, int frame);

		bool contains(MovieClipEntity *child) const;

		MovieClipEntity *getChildAt(int index);

		const MovieClipEntity *getChildAt(int index) const;

		MovieClipEntity *getChildByName(const std::string &name);

		const MovieClipEntity *getChildByName(const std::string &name) const;

		int getChildIndex(MovieClipEntity *child) const;

		std::vector<MovieClipEntity *> getObjectsUnderPoint(const Vector2 &point);

		std::vector<const MovieClipEntity *> getObjectsUnderPoint(const Vector2 &point) const;

		MovieClipEntity *removeChild(MovieClipEntity *child);
		
		void deleteAllChildren();

		void removeAllChildren();

		MovieClipEntity *removeChildAt(int index);

		void removeChildren(int beginIndex, int endIndex);

		void setChildIndex(MovieClipEntity *child, int index);

		void swapChildren(MovieClipEntity *child1, MovieClipEntity *child2);

		void swapChildrenAt(int index1, int index2);

		int getNbChildren() const;

		MovieClipEntity *getParent() const;

		void setFrame(int frame);
		std::deque<MovieClipEntity*> * getCurrentFrameChildren();
		std::deque<MovieClipEntity*> * getCurrentFrameChildren() const;


	private:
		void addChildAt(MovieClipEntity *newChild, int index, ChildArray::iterator frameIterator);

		void setNbFrame(int nbFrames);
		ChildArray::iterator frameIterator;
		MovieClipEntity * parent;

		int getCurrentFrameIndex() const;

		std::deque<MovieClipEntity*>::iterator findChild(MovieClipEntity *child);

		std::deque<MovieClipEntity*>::const_iterator findChild(const MovieClipEntity *child) const;

		void initializeConnections();

		DefaultTimeline *timeline;
		Visibility * visibility;
		int previousFrame;

		ChildArray children;
	};


}

#endif /* defined(BB_DEFAULT_ENTITY_CONTAINER_H) */

