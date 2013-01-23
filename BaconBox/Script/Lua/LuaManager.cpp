#include "BaconBox/Script/Lua/LuaManager.h"

namespace BaconBox {
	LuaManager::LuaManager(){
		L=luaL_newstate();
	 	luaopen_base(L);
        luaopen_table(L);
        luaopen_io(L);
        luaopen_string(L);
        luaopen_math(L);
	}
	
	void LuaManager::doString(const std::string & string){
		luaL_dostring(L, string.c_str());
	}
}
