/**
 * @file
 * @ingroup Display
 */
#ifndef BB_LUA_MANAGER_H
#define BB_LUA_MANAGER_H

#include <string>

#include "BaconBox/Core/Singleton.h"

struct lua_State;

namespace BaconBox {

	class LuaManager : public Singleton {
	public:
		static LuaManager &getInstance();
		void destroyInstance();

		static void doString(const std::string & string);
		static void doFile(const std::string & path);
		static void addToLuaPath(const std::string & path );
		static void addToLuaCPath(const std::string & path );

        static void error(const std::string & error, bool critical = false);
		
		static void printTraceBack();
		static int errorHandler(lua_State *L);
		static int print(lua_State* L);
		static void stackdump(lua_State* l = NULL);

		// FIXME : Now Default is the Singleton instance... add means to have multiple instances.
        static LuaManager& getDefault();
        static void destroyVM();
		void startVM();
		static lua_State * getVM();
		
		static bool criticalError;

	private:
		static LuaManager * instance;

	    LuaManager();
		~LuaManager();

		void internalDoString(const std::string & string);
		void internalDoFile(const std::string & path);
		void internalAddToLuaPath(const std::string & path );
		void internalAddToLuaCPath(const std::string & path );

        void internalError(const std::string & error, bool critical = false);

		lua_State *L;

	};

}
#endif
