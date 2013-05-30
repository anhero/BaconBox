/**
 * @file
 * @ingroup Display
 */
#ifndef BB_LUA_MANAGER_H
#define BB_LUA_MANAGER_H

 	#include <string>

struct lua_State;

namespace BaconBox {

	class LuaManager {
	public:
		LuaManager();
		void doString(const std::string & string);
		void doFile(const std::string & path);
		void addToLuaPath(const std::string & path );

	private:
		lua_State *L;

	};

}
#endif
