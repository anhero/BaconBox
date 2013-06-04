
#ifndef BB_LUAHELPER_H
#define BB_LUAHELPER_H
struct lua_State;
namespace BaconBox {
	class Entity;
	
	class LuaHelper {
	public:
		
		static Entity* getEntityFromLuaEntity(lua_State *L);
	private:

            
	};
	
}

#endif
