#ifndef BB_ENTITY_CONTAINER_H
#define BB_ENTITY_CONTAINER_H

#include <vector>

#include "BaconBox/Core/Component.h"
#include "BaconBox/Vector2.h"

namespace BaconBox {
    class MovieClipEntity;
	class EntityContainer : public Component {
	public:
		BB_ID_HEADER;
		
		EntityContainer();
		
		EntityContainer(const EntityContainer &src);
		
		virtual ~EntityContainer();
		
		virtual void receiveMessage(int senderID, int destID, int message, void *data);
		
		virtual void addChild(Entity *newChild) = 0;
		
		virtual void addChildAt(Entity *newChild, int index) = 0;
		
		virtual bool contains(Entity *child) const = 0;
		
		virtual MovieClipEntity *getChildAt(int index) = 0;
		
		virtual const MovieClipEntity *getChildAt(int index) const = 0;
		
		virtual MovieClipEntity *getChildByName(const std::string &name) = 0;
		
		virtual const MovieClipEntity *getChildByName(const std::string &name) const = 0;
		
		virtual int getChildIndex(Entity *child) const = 0;
		
		virtual std::vector<MovieClipEntity *> getObjectsUnderPoint(const Vector2 &point) = 0;
		
		virtual std::vector<const MovieClipEntity *> getObjectsUnderPoint(const Vector2 &point) const = 0;
		
		virtual MovieClipEntity *removeChild(Entity *child) = 0;
		
		virtual MovieClipEntity *removeChildAt(int index) = 0;
		
		virtual void removeChildren(int beginIndex, int endIndex) = 0;
		
		virtual void setChildIndex(Entity *child, int index) = 0;
		
		virtual void swapChildren(Entity *child1, Entity *child2) = 0;
		
		virtual void swapChildrenAt(int index1, int index2) = 0;
		
		virtual int getNbChildren() const = 0;
		
		virtual MovieClipEntity * getParent() const = 0;

	private:
	};
	
	
	class EntityContainerProxy : public ComponentProxy {
	public:
		EntityContainerProxy(Entity *entity);

		
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
		
	protected:
	    	void setEntityContainer(EntityContainer * entityContainer);

	};
}

#endif /* defined(BB_ENTITY_CONTAINER_H) */

