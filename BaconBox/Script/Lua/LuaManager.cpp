#include "BaconBox/Script/Lua/LuaManager.h"
#include <iostream>

#include "lua.hpp"
#include "BaconBox/Console.h"

extern "C" int luaopen_BaconBox(lua_State* L);

namespace BaconBox {

bool LuaManager::criticalError = false;

LuaManager * LuaManager::instance = NULL;

	LuaManager::LuaManager(){
		L=luaL_newstate();
		luaL_openlibs(L);
        luaopen_BaconBox(L);
	}
	lua_State * LuaManager::getVM(){
		return  getDefault().L;
	}


	void LuaManager::doString(const std::string & string){
        getDefault().internalDoString(string);
	}

	//inspired buy this answer on stackoverflow http://stackoverflow.com/a/4156038
	void LuaManager::addToLuaPath(const std::string & path ){
        getDefault().internalAddToLuaPath(path);
	}

	void LuaManager::addToLuaCPath(const std::string & path ){
        getDefault().internalAddToLuaCPath(path);
	}

	void LuaManager::doFile(const std::string & path){
        getDefault().internalDoFile(path);
	}

        LuaManager& LuaManager::getDefault() {
            if(!instance) instance = new LuaManager();
            return *instance;
        }
        void LuaManager::destroyVM(){
            if(instance)delete instance;
                instance = NULL;
        }
	void LuaManager::printTraceBack(){
		lua_State *L = LuaManager::getVM();
		
		lua_getfield(L, LUA_GLOBALSINDEX, "debug");
		lua_getfield(L, -1, "traceback");
		
		lua_pushvalue(L, 1);  /* pass error message */
		lua_pushinteger(L, 2);  /* skip this function and traceback */
		lua_call(L, 2, 1);  /* call debug.traceback */
		fprintf(stderr, "%s\n", lua_tostring(L, -1));
	}
	
	int LuaManager::errorHandler(lua_State *L) {
		lua_getfield(L, LUA_GLOBALSINDEX, "debug");
		lua_getfield(L, -1, "traceback");
		lua_pushvalue(L, 1);
		lua_pushinteger(L, 2);
		lua_call(L, 2, 1);
		lua_getfield(L, LUA_GLOBALSINDEX, "print");
		lua_pushvalue(L,-2);
		lua_call(L, 1, 0);
		if(LuaManager::criticalError){
			PRLN(lua_tostring(L, -1));
			exit(1);
		}
		return 0;
	}

	//Taken from http://cc.byexamples.com/2008/11/19/lua-stack-dump-for-c/
	void LuaManager::stackdump(){
		lua_State* l = LuaManager::getVM();
		int i;
		int top = lua_gettop(l);
		
		PRLN("total in stack " << top);
		
		for (i = 1; i <= top; i++)
		{  /* repeat for each level */
			int t = lua_type(l, i);
			switch (t) {
				case LUA_TSTRING:  /* strings */
					PRLN(i << " - string: " << lua_tostring(l, i));
					break;
				case LUA_TBOOLEAN:  /* booleans */
					PRLN(i << " - boolean: " << (lua_toboolean(l, i) ? "true" : "false"));
					break;
				case LUA_TNUMBER:  /* numbers */
					PRLN(i << " - number: " << lua_tonumber(l, i));
					break;
				default:  /* other values */
					PRLN(i << " - " << lua_typename(l, t));
					break;
			}
			printf("  ");  /* put a separator */
		}
		printf("\n");  /* end the listing */
	}
	
	void LuaManager::error(const std::string & error, bool critical){
	    getDefault().internalError(error, critical);
	}

        void LuaManager::internalDoString(const std::string & string){
			lua_pushcfunction(L, LuaManager::errorHandler);
            int ret = (luaL_loadstring(L, string.c_str()) || lua_pcall(L, 0, LUA_MULTRET, -2));
            if(ret !=0){
//                std::cout << "An error occured executing a lua string. " <<std::endl;
//                std::cout << "Error : " << lua_tostring(L, -1) << std::endl;
            }
			lua_pop(L,1);

        }
		void LuaManager::internalDoFile(const std::string & path){
			lua_pushcfunction(L, LuaManager::errorHandler);
            int ret = (luaL_loadfile(L, path.c_str()) || lua_pcall(L, 0, LUA_MULTRET, -2));
            if(ret !=0){
//                std::cout << "An error occured executing the lua file: " << path <<std::endl;
//                std::cout << "Error : " << lua_tostring(L, -1) << std::endl;
            }
			lua_pop(L,1);
        }
	
	void LuaManager::internalAddToLuaCPath(const std::string & path ){
		lua_getglobal( L, "package" );
		lua_getfield( L, -1, "cpath" );
		std::string cur_path = lua_tostring( L, -1 );
		cur_path += ';';
		cur_path += path.c_str();
		lua_pop( L, 1 );
		lua_pushstring( L, cur_path.c_str() );
		lua_setfield( L, -2, "cpath" );
		lua_pop( L, 1 );
	}

		void LuaManager::internalAddToLuaPath(const std::string & path ){
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

        void LuaManager::internalError(const std::string & error, bool critical){
			LuaManager::criticalError = critical;
            luaL_error(L, error.c_str());
        }


}
