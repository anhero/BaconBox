#ifndef BB_LUASTATE_H
#define BB_LUASTATE_H

#include "BaconBox/Core/Component.h"
#include "BaconBox/Core/Entity.h"

struct lua_State;

namespace BaconBox {
	class LuaState : public Component {
	public:
		BB_ID_HEADER;
		
		LuaState();
		~LuaState();
		void setLuaClass(lua_State * L);
		void reloadLuaClass();

		void update();
		void render();
					
		virtual void receiveMessage(int senderID, int destID, int message, void *data);
		
	private:
		static int EMPTY_LUA_REF;
	    
		int table_index;
		int update_index;
		int userData_index;
		lua_State * L;
	};


	class LuaStateProxy : public ComponentProxy{
	public:
		LuaStateProxy(Entity* entity, bool mustAddComponent = true);
		void reloadLuaClass();
		void setLuaClass(lua_State * L);
	private:		

	};
}

#endif
