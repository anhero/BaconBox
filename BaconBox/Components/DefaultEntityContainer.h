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
	class EntityContainerLooper;
	
	class DefaultEntityContainer : public EntityContainer {
		friend class EntityContainerLooper;
	public:
		typedef std::map<int, std::deque<Entity*> > ChildArray;
		
		DefaultEntityContainer();
		
//		DefaultEntityContainer(const DefaultEntityContainer &src);
		
		virtual ~DefaultEntityContainer();
		
//		DefaultEntityContainer &operator=(const DefaultEntityContainer &src);
//		
//		DefaultEntityContainer *clone() const;
		
		void receiveMessage(int senderID, int destID, int message, void *data);
		
		/**
		 * Updates all the child entities.
		 */
		void update();
		
		/**
		 * Renders all the child entities.
		 */
		void render();
		
		void addChild(Entity *newChild);
		
		void addChild(Entity *newChild, int frame);
		
		void addChildAt(Entity *newChild, int index);
		
		void addChildAt(Entity *newChild, int index, int frame);
		
		bool contains(Entity *child) const;
		
		Entity *getChildAt(int index);
		
		const Entity *getChildAt(int index) const;
		
		Entity *getChildByName(const std::string &name);
		
		const Entity *getChildByName(const std::string &name) const;
		
		int getChildIndex(Entity *child) const;
		
		std::vector<Entity *> getObjectsUnderPoint(const Vector2 &point);
		
		std::vector<const Entity *> getObjectsUnderPoint(const Vector2 &point) const;
		
		Entity *removeChild(Entity *child);
		
		void removeAllChildren();
		
		Entity *removeChildAt(int index);
		
		void removeChildren(int beginIndex, int endIndex);
		
		void setChildIndex(Entity *child, int index);
		
		void swapChildren(Entity *child1, Entity *child2);
		
		void swapChildrenAt(int index1, int index2);	
	
		int getNbChildren() const;
		
		Entity *getParent() const;

		void setFrame(int frame);
		std::deque<Entity*> * getCurrentFrameChildren();

	private:
		ChildArray::iterator frameIterator;		
		Entity * parent;
		
		int getCurrentFrameIndex() const;
		
		std::deque<Entity*>::iterator findChild(Entity *child);
		
		std::deque<Entity*>::const_iterator findChild(const Entity *child) const;
		
		void initializeConnections();
		
		DefaultTimeline *timeline;
		int previousFrame;
		
		ChildArray children;
	};
	
	
}

#endif /* defined(BB_DEFAULT_ENTITY_CONTAINER_H) */

