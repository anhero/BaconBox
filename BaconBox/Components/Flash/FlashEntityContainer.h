#ifndef BB_FLASH_ENTITY_CONTAINER_H
#define BB_FLASH_ENTITY_CONTAINER_H

#include <vector>
#include "BaconBox/Core/Component.h"
#include "BaconBox/Vector2.h"
#include "BaconBox/Components/EntityContainer.h"


namespace BaconBox {
	class FlashEntityContainer : public EntityContainer {
	public:
		
		FlashEntityContainer();
		
		FlashEntityContainer(const FlashEntityContainer &src);
		
		virtual ~FlashEntityContainer();
		
		virtual void receiveMessage(int senderID, int destID, int message, void *data);
		
		void addChild(Entity *newChild);
		
		void addChildAt(Entity *newChild, int index);
		
		bool contains(Entity *child) const;
		
		Entity *getChildAt(int index);

		const Entity *getChildAt(int index) const;
		
		Entity *getChildByName(const std::string &name);
		
		const Entity *getChildByName(const std::string &name) const;
		
		int getChildIndex(Entity *child) const;
		
		std::vector<Entity *> getObjectsUnderPoint(const Vector2 &point);
		
		std::vector<const Entity *> getObjectsUnderPoint(const Vector2 &point) const;
		
		Entity *removeChild(Entity *child);
		
		Entity *removeChildAt(int index);
		
		void removeChildren(int beginIndex, int endIndex);
		
		void setChildIndex(Entity *child, int index);
		
		void swapChildren(Entity *child1, Entity *child2);
		
		void swapChildrenAt(int index1, int index2);
		
		int getNbChildren() const;
		
		Entity * getParent() const;

	private:
	};
}

#endif /* defined(BB_FLASH_ENTITY_CONTAINER_H) */

