
#ifndef BB_LUAHELPER_H
#define BB_LUAHELPER_H
#include "BaconBox/Script/Lua/LuaCallback.h"
struct lua_State;
namespace BaconBox {
	class Entity;
	class MovieClipEntity;
	
	class LuaHelper {
	public:
		static void* getPointerFromLuaUserData(lua_State *L, bool pop = true);
		static Entity* getEntityFromLuaEntity(lua_State *L);
		static MovieClipEntity* getMovieClipEntityFromLuaEntity(lua_State *L);
		static void connectSignal1(lua_State*L, BaconBox::LuaCallback * cb);
		static void connectSignal0(lua_State*L, BaconBox::LuaCallback * cb);
	private:

        
	};
	
}

#endif
