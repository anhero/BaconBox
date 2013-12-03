#include "LuaCallback.h"

#include "BaconBox/Console.h"
#include "lua.hpp"
#include "BaconBox/Helper/Lua/LuaHelper.h"
#include "swigluarun.h"
using namespace BaconBox;

int LuaCallback::EMPTY_LUA_REF = -1;

swig_type_info * getTypeByName(lua_State* L, const char * name);

LuaCallback::LuaCallback(lua_State * L, const std::string & type):sigly::HasSlots<sigly::SingleThreaded>(), swigType1(NULL), table_index(EMPTY_LUA_REF), function_index(EMPTY_LUA_REF){
	this->L = L;
	if(lua_istable(L, -1)){
		lua_getfield(L, -1, "call");
		if(lua_isfunction(L, -1)){
		    function_index = luaL_ref(L, LUA_REGISTRYINDEX);
			table_index = luaL_ref(L, LUA_REGISTRYINDEX);
			void * signal = LuaHelper::getPointerFromLuaUserData(L, false);
			lua_rawgeti(L, LUA_REGISTRYINDEX,table_index);
			lua_getfield(L, -1, "addCWrapper");
			lua_rawgeti(L, LUA_REGISTRYINDEX,table_index);
			lua_pushlightuserdata(L, signal);
			SWIG_NewPointerObj(L, static_cast<void*>(this), getTypeByName(L, "LuaCallback"), 0);
			
			int ret = lua_pcall(L, 3, 0, 0);
			if(ret !=0){
				std::cout << "An error occured calling LuaCallback::LuaCallback(...). " <<std::endl;
				std::cout << "Error : " << lua_tostring(L, -1) << std::endl;
			}
			lua_pop (L, 1);

			
		}
	}
	else{
		Console__error("Can't construct a LuaCallback, top of the stack wasn't a table");
	}
	
	if(type != ""){
		swigType1 = getTypeByName(L, type.c_str());
	}
}

void LuaCallback::call(void* param) {
	lua_rawgeti(L, LUA_REGISTRYINDEX,function_index);
	lua_rawgeti(L, LUA_REGISTRYINDEX,table_index);
	SWIG_NewPointerObj(L, param, swigType1, 0);
	int ret = lua_pcall(L, 2, 0, 0);
	if(ret !=0){
		std::cout << "An error occured executing a LuaCallback. " <<std::endl;
		std::cout << "Error : " << lua_tostring(L, -1) << std::endl;
	}
};

void LuaCallback::call(){
	if(function_index == EMPTY_LUA_REF)return;
	lua_rawgeti(L, LUA_REGISTRYINDEX,function_index);
	lua_rawgeti(L, LUA_REGISTRYINDEX,table_index);
	
	int ret = lua_pcall(L, 1, 0, 0);
	if(ret !=0){
		std::cout << "An error occured executing a LuaCallback. " <<std::endl;
		std::cout << "Error : " << lua_tostring(L, -1) << std::endl;
	}
}
