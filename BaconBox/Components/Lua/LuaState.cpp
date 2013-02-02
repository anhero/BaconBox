#include "LuaState.h"



#include "lua.hpp"
#include "BaconBox/Console.h"

namespace BaconBox {
	 BB_ID_IMPL(LuaState);
	
	 int LuaState::EMPTY_LUA_REF = -1;
	 
	LuaState::LuaState() : Component(), table_index(EMPTY_LUA_REF), update_index(EMPTY_LUA_REF), userData_index(EMPTY_LUA_REF) {
	}
	LuaState::~LuaState(){
		if(L){
			if(table_index != EMPTY_LUA_REF){
				luaL_unref(L, LUA_REGISTRYINDEX, table_index);
			}
			if(update_index != EMPTY_LUA_REF){
				luaL_unref(L, LUA_REGISTRYINDEX, update_index);
			}
		}
	}

	void LuaState::update(){
	    if(update_index == EMPTY_LUA_REF)return;
		lua_rawgeti(L, LUA_REGISTRYINDEX,update_index);
		lua_rawgeti(L, LUA_REGISTRYINDEX,table_index);
		lua_rawgeti(L, LUA_REGISTRYINDEX,userData_index);
		int ret = lua_pcall(L, 2, 0, 0);
		if(ret !=0){
			std::cout << "An error occured updating a LuaState. " <<std::endl;
			std::cout << "Error : " << lua_tostring(L, -1) << std::endl;
		}
	}

	void LuaState::render(){

	}
	
	void LuaState::reloadLuaClass(){
		lua_rawgeti(L, LUA_REGISTRYINDEX,table_index);
		lua_getfield(L, -1, "update");
		if(lua_isnil(L, -1)){
		    lua_pop(L, -1);
		}
		else{
		    update_index = luaL_ref(L, LUA_REGISTRYINDEX);
		}
	}

	void LuaState::setLuaClass(lua_State * L){
	    if(!lua_istable(L,-1)){
		Console::error("Lua Parameter of LuaState::setLuaClass must be a table");
		return;
	    }
	    if(!lua_isuserdata(L,-2)){
		Console::error("LuaState::setLuaClass must be called on a LuaState or LuaStateProxy object."); 
		return;
	    }
	    table_index = luaL_ref(L, LUA_REGISTRYINDEX);
	    userData_index = luaL_ref(L, LUA_REGISTRYINDEX);
	    this->L = L;
	   
	    this->reloadLuaClass();
	}

	void LuaState::receiveMessage(int senderID, int destID, int message, void *data) {
	}

	LuaStateProxy::LuaStateProxy(Entity * entity, bool mustAddComponent): BB_PROXY_CONSTRUCTOR(new LuaState()){
	}

	void LuaStateProxy::reloadLuaClass(){
	    reinterpret_cast<LuaState*>(component)->reloadLuaClass();
	}
	
	void LuaStateProxy::setLuaClass(lua_State * L){
		if(component){
			reinterpret_cast<LuaState*>(component)->setLuaClass(L);
		}
		else{
			component = entity->getComponent(LuaState::ID);
			if(!component) Console::error("Call to setLuaClass on an entity with no LuaStateComponent!");
			reinterpret_cast<LuaState*>(component)->setLuaClass(L);
		}
	}


}