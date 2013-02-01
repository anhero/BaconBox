#include "LuaState.h"



#include "lua.hpp"
#include "BaconBox/Console.h"

namespace BaconBox {
	 BB_ID_IMPL(LuaState);
	
	LuaState::LuaState() : Component(), table_index(-1) {
		setName("LuaState");
	}
	LuaState::~LuaState(){
		if(L){
			if(table_index){
				luaL_unref(L, LUA_REGISTRYINDEX, table_index);
			}
			if(update_index){
				luaL_unref(L, LUA_REGISTRYINDEX, update_index);
			}
		}
	}

	void LuaState::update(){
	    if(update_index == -1)return;
		lua_rawgeti(L, LUA_REGISTRYINDEX,update_index);
		lua_rawgeti(L, LUA_REGISTRYINDEX,table_index);
		int ret = lua_pcall(L, 1, 0, 0);
		if(ret !=0){
			std::cout << "An error occured updating a LuaState. " <<std::endl;
			std::cout << "Error : " << lua_tostring(L, -1) << std::endl;
		}
	}

	void LuaState::render(){

	}

	void LuaState::setLuaClass(lua_State * L){
		lua_getfield(L, -1, "update");
		update_index = luaL_ref(L, LUA_REGISTRYINDEX);
		table_index = luaL_ref(L, LUA_REGISTRYINDEX);
		this->L = L;
	}

	void LuaState::receiveMessage(int senderID, int destID, int message, void *data) {
            //if(destID != LuaState::ID)return;
	}

	LuaStateProxy::LuaStateProxy(Entity * entity, bool mustAddComponent): entity(entity){
		if(mustAddComponent){
			luaState= new LuaState();
			entity->addComponent(luaState);
		}
	}

	void LuaStateProxy::setLuaClass(lua_State * L){
		if(luaState){
			luaState->setLuaClass(L);
		}
		else{
			luaState = reinterpret_cast<LuaState*>(entity->getComponent(LuaState::ID));
			if(!luaState) Console::error("Call to setLuaClass on an entity with no LuaStateComponent!");
			luaState->setLuaClass(L);
		}
	}


}