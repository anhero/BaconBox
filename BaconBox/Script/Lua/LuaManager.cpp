#include "BaconBox/Script/Lua/LuaManager.h"
#include <iostream>

extern "C" int luaopen_BaconBox(lua_State* L); 

namespace BaconBox {
	LuaManager::LuaManager(){
		L=luaL_newstate();
	 	luaopen_base(L);
        luaopen_table(L);
        luaopen_io(L);
        luaopen_string(L);
        luaopen_math(L);
	luaopen_BaconBox(L);
	}
	
	void LuaManager::doString(const std::string & string){
		luaL_dostring(L, string.c_str());
	}

	void LuaManager::doFile(const std::string & path){
		int ret = luaL_dofile(L, path.c_str());
		if(ret !=0){
			std::cout << "An error occured loading the lua file: " << path <<std::endl;
			std::cout << "Error : " << lua_tostring(L, -1) << std::endl;
		}
	}
}
