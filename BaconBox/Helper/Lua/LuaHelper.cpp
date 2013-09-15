#include "LuaHelper.h"

#include "BaconBox/Core/Entity.h"
#include "BaconBox/Console.h"
#include "lua.hpp"

using namespace BaconBox;

struct swig_type_info;

int luaUserDataconvertPtr(lua_State *L, int index, void **ptr, swig_type_info *type, int flags);

namespace BaconBox {

	void *LuaHelper::getPointerFromLuaUserData(lua_State *L, bool pop) {
		void *ptr;
		luaUserDataconvertPtr(L, -1, (void **)(&ptr), NULL, 0);

		if (pop) {
			lua_pop(L, 1);
		}

		return ptr;
	}

	Entity *LuaHelper::getEntityFromLuaEntity(lua_State *L) {
		if (lua_istable(L, -1)) {
			lua_getfield(L, -1, "entity");
			Entity *entity = reinterpret_cast<Entity *>(getPointerFromLuaUserData(L));

			return entity;
		}

		Console__error("Can't return an entity in LuaHelper::getEntityFromLuaEntity.");
		return NULL;
	}

	MovieClipEntity *LuaHelper::getMovieClipEntityFromLuaEntity(lua_State *L) {
		if (lua_istable(L, -1)) {
			lua_getfield(L, -1, "entity");
			MovieClipEntity *entity = reinterpret_cast<MovieClipEntity *>(getPointerFromLuaUserData(L));

			return entity;
		}

		Console__error("Can't return an entity in LuaHelper::getEntityFromLuaEntity.");
		return NULL;
	}

	void LuaHelper::connectSignal1(lua_State *L, BaconBox::LuaCallback *cb) {
		if (lua_isuserdata(L, -1)) {
			sigly::Signal1<void *> *signal = reinterpret_cast<sigly::Signal1<void *> *>(BaconBox::LuaHelper::getPointerFromLuaUserData(L));
			signal->connect(cb, &BaconBox::LuaCallback::call);

		} else {
			Console__error("connectSignal wasn't able to connect signal, wrong parameter were given.");
		}
	}

	void LuaHelper::connectSignal0(lua_State *L, BaconBox::LuaCallback *cb) {
		if (lua_isuserdata(L, -1)) {
			sigly::Signal0<> *signal = reinterpret_cast<sigly::Signal0<> *>(BaconBox::LuaHelper::getPointerFromLuaUserData(L));
			signal->connect(cb, &BaconBox::LuaCallback::call);

		} else {
			Console__error("connectSignal wasn't able to connect signal, wrong parameter were given.");
		}
	}
}
