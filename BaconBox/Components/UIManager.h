#ifndef BB_UIMANAGER_H
#define BB_UIMANAGER_H

#include <vector>
#include <list>
#include <set>
#include "BaconBox/Core/Component.h"
#include "BaconBox/MovieClipEntity/MovieClipEntity.h"
#include <list>

#ifdef BB_LUA
struct lua_State;
#endif //BB_LUA
namespace BaconBox {
	class UIManager : public Component {
	public:
		BB_ID_HEADER;
		
		UIManager();
		~UIManager();
		
		void addClickable(MovieClipEntity *newEntity);
		void removeClickable(MovieClipEntity *newEntity);

#ifdef BB_LUA
		void addClickable(lua_State * L);
		void removeClickable(lua_State * L);
#endif //BB_LUA
		
		virtual void receiveMessage(int senderID, int destID, int message, void *data);
		

	private:
		void disconnect();
		void connect();
		
		void pointerButtonRelease(PointerButtonSignalData data);
		void pointerButtonPress(PointerButtonSignalData data);
		void pointerMove(PointerSignalData data);
		MovieClipEntity* lastOver;
		MovieClipEntity* currentlyPressed;
		Vector2 lastPressed;

		std::list<MovieClipEntity*> clickable;

	};
	
	class UIManagerProxy : public ComponentProxy {
	public:
		UIManagerProxy(Entity *entity, bool mustAddComponent = true);
		void addClickable(MovieClipEntity *newEntity);
		void removeClickable(MovieClipEntity *newEntity);
#ifdef BB_LUA
		void addClickable(lua_State * L);
		void removeClickable(lua_State * L);
#endif //BB_LUA
	};
}

#endif
