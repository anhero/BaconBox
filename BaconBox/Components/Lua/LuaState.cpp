#include "LuaState.h"

#include "BaconBox/Core/Entity.h"

#include "lua.hpp"
#include <iostream>

namespace BaconBox {
	 BB_ID_IMPL(LuaState);
	
	LuaState::LuaState() : Component() {
		setName("LuaState");
	}

	void LuaState::update(){
		lua_rawgeti(L, LUA_REGISTRYINDEX,table_index);
		lua_rawgeti(L, LUA_REGISTRYINDEX,update_index);
		lua_pcall(L, 1, 0, 0);
	}

	void LuaState::render(){

	}

	void LuaState::setLuaClass(lua_State * L){
		table_index = luaL_ref(L, LUA_REGISTRYINDEX);
		lua_getfield(L, -1, "update");
		update_index = luaL_ref(L, LUA_REGISTRYINDEX);
		this->L = L;
	}

	void LuaState::receiveMessage(int senderID, int destID, int message, void *data) {
            //if(destID != LuaState::ID)return;
	}
}