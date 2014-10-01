#ifndef BB_ENTITY_CONTAINER_H
#define BB_ENTITY_CONTAINER_H

#include <vector>

#include "BaconBox/Core/Component.h"
#include "BaconBox/Vector2.h"

#ifdef BB_LUA
#include "BaconBox/Components/Lua/LuaEntity.h"
#endif

#ifdef BB_LUA
struct lua_State;
#endif //BB_LUA

namespace BaconBox {
    class MovieClipEntity;
	class EntityContainer : public Component {
	public:
		BB_ID_HEADER;

		EntityContainer();

		EntityContainer(const EntityContainer &src);

		virtual ~EntityContainer();

		virtual void receiveMessage(int senderID, int destID, int message, void *data);

		virtual void propagateMessage(int senderID, int destID, int message, void *data) = 0;

		virtual void addChild(MovieClipEntity *newChild) = 0;

		virtual void addChildAt(MovieClipEntity *newChild, int index) = 0;

		virtual bool contains(MovieClipEntity *child) const = 0;

		virtual MovieClipEntity *getChildAt(int index) = 0;

		virtual const MovieClipEntity *getChildAt(int index) const = 0;

		virtual MovieClipEntity *getChildByName(const std::string &name) = 0;

		virtual const MovieClipEntity *getChildByName(const std::string &name) const = 0;

		virtual int getChildIndex(MovieClipEntity *child) const = 0;

		virtual std::vector<MovieClipEntity *> getObjectsUnderPoint(const Vector2 &point) = 0;

		virtual std::vector<const MovieClipEntity *> getObjectsUnderPoint(const Vector2 &point) const = 0;

		virtual MovieClipEntity *removeChild(MovieClipEntity *child) = 0;

		virtual MovieClipEntity *removeChildAt(int index) = 0;

		virtual void removeChildren(int beginIndex, int endIndex) = 0;

		virtual void setChildIndex(MovieClipEntity *child, int index) = 0;

		virtual void swapChildren(MovieClipEntity *child1, MovieClipEntity *child2) = 0;

		virtual void swapChildrenAt(int index1, int index2) = 0;

		virtual int getNbChildren() const = 0;

		virtual MovieClipEntity * getParent() const = 0;


	private:
	};


	class EntityContainerProxy : public ComponentProxy {
	public:
		EntityContainerProxy(MovieClipEntity *entity);

		void addChild(MovieClipEntity *newChild);
		
#ifdef BB_LUA
		void addChild(lua_State *L);
		MovieClipEntity *removeChild(lua_State *L);
#endif //BB_LUA

		void addChildAt(MovieClipEntity *newChild, int index);

		bool contains(MovieClipEntity *child) const;

		MovieClipEntity *getChildAt(int index);

		const MovieClipEntity *getChildAt(int index) const;

		MovieClipEntity *getChildByName(const std::string &name);

		const MovieClipEntity *getChildByName(const std::string &name) const;

		int getChildIndex(MovieClipEntity *child) const;

		std::vector<MovieClipEntity *> getObjectsUnderPoint(const Vector2 &point);

		std::vector<const MovieClipEntity *> getObjectsUnderPoint(const Vector2 &point) const;

		MovieClipEntity *removeChild(MovieClipEntity *child);




		MovieClipEntity *removeChildAt(int index);

		void removeChildren(int beginIndex, int endIndex);

		void setChildIndex(MovieClipEntity *child, int index);

		void swapChildren(MovieClipEntity *child1, MovieClipEntity *child2);

		void swapChildrenAt(int index1, int index2);

		int getNbChildren() const;

		 MovieClipEntity * getParent() const;

		 void propagateMessage(int senderID, int destID, int message, void *data);

	protected:
	    	void setEntityContainer(EntityContainer * entityContainer);

	};
}

#endif /* defined(BB_ENTITY_CONTAINER_H) */

