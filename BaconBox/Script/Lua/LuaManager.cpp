#include "BaconBox/Script/Lua/LuaManager.h"
#include <iostream>

#include "lua.hpp"

extern "C" int luaopen_BaconBox(lua_State* L);

namespace BaconBox {
	LuaManager::LuaManager(){
		L=luaL_newstate();
		luaL_openlibs(L);
	luaopen_BaconBox(L);
	}
	
	void LuaManager::doString(const std::string & string){
		int ret = luaL_dostring(L, string.c_str());
		if(ret !=0){
			std::cout << "An error occured parsing a lua string. " <<std::endl;
			std::cout << "Error : " << lua_tostring(L, -1) << std::endl;
		}
	}
	
	//inspired buy this answer on stackoverflow http://stackoverflow.com/a/4156038
	void LuaManager::addToLuaPath(const std::string & path ){
		lua_getglobal( L, "package" );
		lua_getfield( L, -1, "path" );
		std::string cur_path = lua_tostring( L, -1 ); 
		cur_path += ';'; 
		cur_path += path.c_str();
		lua_pop( L, 1 ); 
		lua_pushstring( L, cur_path.c_str() ); 
		lua_setfield( L, -2, "path" ); 
		lua_pop( L, 1 ); 
	}

	void LuaManager::doFile(const std::string & path){
		int ret = luaL_dofile(L, path.c_str());
		if(ret !=0){
			std::cout << "An error occured parsing the lua file: " << path <<std::endl;
			std::cout << "Error : " << lua_tostring(L, -1) << std::endl;
		}
	}
}
