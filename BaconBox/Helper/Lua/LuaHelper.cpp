#include "LuaHelper.h"

#include "BaconBox/Core/Entity.h"
#include "BaconBox/Console.h"
#include "lua.hpp"

struct swig_type_info;


int luaUserDataconvertPtr(lua_State* L,int index,void** ptr,swig_type_info *type,int flags);


using namespace BaconBox;
Entity* LuaHelper::getEntityFromLuaEntity(lua_State *L){
	if(lua_istable(L,-1)){
		lua_getfield(L, -1, "entity");
		Entity * entity;
		luaUserDataconvertPtr(L, -1, (void**)(&entity), NULL, 0);
		return entity;
	}
	
	Console__error("Can't return an entity in LuaHelper::getEntityFromLuaEntity.");
	return NULL;
}
