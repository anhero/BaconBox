#ifndef BB_DEFAULT_ENTITY_CONTAINER_H
#define BB_DEFAULT_ENTITY_CONTAINER_H

#include <vector>
#include <map>
#include <string>

#include "BaconBox/Components/EntityContainer.h"
#include "BaconBox/Helper/Range.h"

namespace BaconBox {
	class Timeline;
	
	class DefaultEntityContainer : public EntityContainer {
	public:
		DefaultEntityContainer();
		
		DefaultEntityContainer(const DefaultEntityContainer &src);
		
		virtual ~DefaultEntityContainer();
		
		DefaultEntityContainer &operator=(const DefaultEntityContainer &src);
		
		DefaultEntityContainer *clone() const;
		
		void receiveMessage(int senderID, int destID, int message, void *data);
		
		Entity *addChild(Entity *newChild);
		
		Entity *addChildAt(Entity *newChild, int index);
		
		bool contains(Entity *child) const;
		
		Entity *getChildAt(int index);
		
		const Entity *getChildAt(int index) const;
		
		Entity *getChildByName(const std::string &name);
		
		const Entity *getChildByName(const std::string &name) const;
		
		int getChildIndex(Entity *child) const;
		
		std::vector<Entity *> getObjectsUnderPoint(const Vector2 &point) const;
		
		Entity *removeChild(Entity *child);
		
		Entity *removeChildAt(int index);
		
		Entity *removeChildren(int beginIndex, int endIndex);
		
		void setChildIndex(Entity *child, int index);
		
		void swapChildren(Entity *child1, Entity *child2);
		
		void swapChildrenAt(int index1, int index2);
		
		int getNbChildren() const;
	private:
		void initializeConnections();
		
		void updateConnections();
		
		Timeline *timeline;
		
		std::map<std::string, Entity *> childrenByName;
		
		std::vector<std::map<Range<int>, Entity *, Range<int>::Comparator> > children;
	};
}

#endif /* defined(BB_DEFAULT_ENTITY_CONTAINER_H) */

