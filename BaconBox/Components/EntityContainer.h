#ifndef BB_ENTITY_CONTAINER_H
#define BB_ENTITY_CONTAINER_H

#include <vector>

#include "BaconBox/Core/Component.h"
#include "BaconBox/Vector2.h"

namespace BaconBox {
	class EntityContainer : public Component {
	public:
		BB_ID_HEADER;
		
		EntityContainer();
		
		EntityContainer(const EntityContainer &src);
		
		virtual ~EntityContainer();
		
		virtual void receiveMessage(int senderID, int destID, int message, void *data);
		
		virtual Entity *addChild(Entity *newChild) = 0;
		
		virtual Entity *addChildAt(Entity *newChild, int index) = 0;
		
		virtual bool contains(Entity *child) const = 0;
		
		virtual Entity *getChildAt(int index) = 0;
		
		virtual const Entity *getChildAt(int index) const = 0;
		
		virtual Entity *getChildByName(const std::string &name) = 0;
		
		virtual const Entity *getChildByName(const std::string &name) const = 0;
		
		virtual int getChildIndex(Entity *child) const = 0;
		
		virtual std::vector<Entity *> getObjectsUnderPoint(const Vector2 &point) = 0;
		
		virtual std::vector<const Entity *> getObjectsUnderPoint(const Vector2 &point) const = 0;
		
		virtual Entity *removeChild(Entity *child) = 0;
		
		virtual Entity *removeChildAt(int index) = 0;
		
		virtual void removeChildren(int beginIndex, int endIndex) = 0;
		
		virtual void setChildIndex(Entity *child, int index) = 0;
		
		virtual void swapChildren(Entity *child1, Entity *child2) = 0;
		
		virtual void swapChildrenAt(int index1, int index2) = 0;
		
		virtual int getNbChildren() const = 0;
	private:
	};
}

#endif /* defined(BB_ENTITY_CONTAINER_H) */

