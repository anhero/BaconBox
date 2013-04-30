#ifndef BB_FLASH_ENTITY_CONTAINER_H
#define BB_FLASH_ENTITY_CONTAINER_H

#include <vector>
#include "BaconBox/Core/Component.h"
#include "BaconBox/Vector2.h"
#include "BaconBox/Components/EntityContainer.h"
#include "MovieClipHolder.h"

namespace BaconBox {
	class FlashEntityContainer : public EntityContainer {
	public:
		
		FlashEntityContainer();
		
		FlashEntityContainer(const FlashEntityContainer &src);
		
		virtual ~FlashEntityContainer();
		
		void receiveMessage(int senderID, int destID, int message, void *data);
		
		void addChild(Entity *newChild);
		
		void addChildAt(Entity *newChild, int index);
		
		bool contains(Entity *child) const;
		
		MovieClipEntity *getChildAt(int index);

		const MovieClipEntity *getChildAt(int index) const;
		
		MovieClipEntity *getChildByName(const std::string &name);
		
		const MovieClipEntity *getChildByName(const std::string &name) const;
		
		int getChildIndex(Entity *child) const;
		
		std::vector<MovieClipEntity *> getObjectsUnderPoint(const Vector2 &point);
		
		std::vector<const MovieClipEntity *> getObjectsUnderPoint(const Vector2 &point) const;
		
		MovieClipEntity *removeChild(Entity *child);
		
		MovieClipEntity *removeChildAt(int index);
		
		void removeChildren(int beginIndex, int endIndex);
		
		void setChildIndex(Entity *child, int index);
		
		void swapChildren(Entity *child1, Entity *child2);
		
		void swapChildrenAt(int index1, int index2);
		
		int getNbChildren() const;
		
		MovieClipEntity * getParent() const;

	private:
		MovieClipHolder * movieClipHolder;
		void initializeConnections();
		MovieClipEntity *internalgetChildByName(const std::string &name) const;
		MovieClipEntity *internalGetChildAt(int index) const;



	};
}

#endif /* defined(BB_FLASH_ENTITY_CONTAINER_H) */

