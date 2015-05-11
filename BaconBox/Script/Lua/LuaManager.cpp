#include "BaconBox/Script/Lua/LuaManager.h"
#include <iostream>

#include <lua.hpp>
#include "BaconBox/Console.h"
#include <sstream>

#include "BaconBox/Core/Engine.h"

extern "C" int luaopen_BaconBox(lua_State* L);

namespace BaconBox {

	BB_SINGLETON_IMPL(LuaManager);

	LuaManager& LuaManager::getDefault() {
		return getInstance();
	}

	void LuaManager::destroyVM(){
		lua_close(getInstance().L);
		getInstance().startVM();
	}

	bool LuaManager::criticalError = false;

	void LuaManager::startVM() {
		L=luaL_newstate();
		luaL_openlibs(L);
		luaopen_BaconBox(L);
		#ifdef BB_ANDROID
		static const struct luaL_reg printlib [] = {
			{"print", LuaManager::print},
			{NULL, NULL} /* end of array */
		};
		lua_getglobal(L, "_G");
		luaL_register(L, NULL, printlib);
		lua_pop(L, 1);
		#endif

		// Register our custom loadfile and custom open.
		static const luaL_reg bb_fs_loadfile_open[] = {
			{"loadfile", LuaManager::loadfile},
			{"open", LuaManager::open},
			{NULL, NULL}
		};
		lua_getglobal(L, "_G");
		luaL_register(L, NULL, bb_fs_loadfile_open);
		lua_pop(L, 1);

		// We register ourselves to the package loaders.
		// http://pgl.yoyo.org/luai/i/package.loaders

		// We are replacing index '2'. This stops the default loader from
		// loading files from the real filesystem.

		// Get package.loaders.
		lua_getglobal(L, "package");
		lua_getfield(L, -1, "loaders");

		// Insert our loader.
		lua_pushcfunction(L, LuaManager::packageloader);
		LuaManager::table_insert(L, -2, -1, 2);
		lua_pop(L, 3);

		// Run this code at first.
		// It basically destroys io, file and some functions of os.
		// If we want to de-sandbox the lua interpreter, this would be here.
		// The user will need to use the BaconBox FileSystem/File API for file manipulations.
		const std::string code_str(
			"for k,v in pairs(io) do io[k] = nil end;"
			"io = nil;"
			"for k,v in pairs(file) do file[k] = nil end;"
			"file = nil;"
			// Remove os.[execute|remove|rename]
			"os.execute = nil;"
			"os.remove = nil;"
			"os.rename = nil;"
		);
		LuaManager::internalDoString(L, code_str);
	}

	lua_State * LuaManager::getVM(){
		return  getInstance().L;
	}

	LuaManager::LuaManager(){
		startVM();
	}

	LuaManager::~LuaManager(){
		lua_close(L);
	}

	int LuaManager::print(lua_State* L) {
		int nargs = lua_gettop(L);
		std::stringstream ss;
		for (int i=1; i <= nargs; i++) {
			int t = lua_type(L, i);
			switch (t) {
					case LUA_TSTRING:  /* strings */
						ss << lua_tostring(L, i) << " ";
						break;
					case LUA_TBOOLEAN:  /* booleans */
						ss << (lua_toboolean(L, i) ? "true" : "false") << " ";
						break;
					case LUA_TNUMBER:  /* numbers */
						ss << lua_tonumber(L, i) << " ";
						break;
					default:  /* other values */
						ss << lua_typename(L, t) << " ";
						break;
				};
		}

		PRLN(ss.str());

		return 0;
	}

	const char* LuaManager::reader(lua_State *L, void *data, size_t *size) {
		reader_state * state = (reader_state*)data;
		unsigned int to_read = BUFSIZ;
		if ((state->amount_read + to_read) > state->file->size()) {
			to_read = state->file->size() - state->amount_read;
		}
		// TODO : Error checking.
		state->file->fillBuffer(state->buffer, state->amount_read, to_read);
		state->amount_read += to_read;

		*size = (size_t) to_read;
		return state->buffer;
	}

	int LuaManager::loadfile(lua_State *L) {
		// TODO : Read path from lua stac.
		const char * path = luaL_checkstring(L, 1);
		return LuaManager::loadfile(L, path);
	}
	int LuaManager::loadfile(lua_State *L, const std::string path) {
		reader_state state;
		state.file = FileSystem::open(path);
		if (lua_load(L, LuaManager::reader, &state, path.c_str())) {
			return lua_error(L);
		}
		return 1;
	}
	int LuaManager::open(lua_State *L) {
		Console__error("LuaManager::open() not implemented yet!");
		return 1;
	}

	// package loader used to make require load stuff from our VFS.
	// It respects package.path.
	int LuaManager::packageloader(lua_State *L) {
		// Prepares the argument to a filename.
		const char * module = luaL_checkstring(L, 1);
		lua_pushstring(L, "/");
		luaL_gsub(L, module, ".", "/");
		lua_concat(L, 2);

		// Read that name
		const char * filename = lua_tostring(L, 2);

		// Get the lua package.path.
		std::string luapath = getLuaPath();
		// Append a delimiter to the string to make the loop easier to deal with.
		luapath.append(std::string(";"));
		std::string token;
		size_t pos = 0;

		// Iterate until either the end or we find a proper path.
		while ((pos = luapath.find(";")) != std::string::npos) {
			// Get the token.
			token = luapath.substr(0, pos);

			// Replace '?' with the filename
			size_t replacement_pos = token.find('?');
			if (replacement_pos != std::string::npos) {
				token.replace(replacement_pos, 1, filename);
			}

			// Found the file?
			if (FileSystem::exists(token)) {	break;}

			// Erase from our copy of the lua path what we have tried.
			luapath.erase(0, pos + 1); // 1 = delimiter length, ';'.
		}

		// Verify that we have found a valid path.
		if (token == "") {
			lua_pushfstring(L, "\n\t[BBVFS]: no file '%s'", filename);
			return 1;
		}
		// Pop the original string and push our new filename.
		filename = token.c_str();
		lua_pop(L, 1);
		lua_pushstring(L, filename);

		// Call loadfile.
		lua_pushcfunction(L, LuaManager::loadfile);
		lua_insert(L, 2);
		lua_call(L, 1, 1);

		return 1;
	}

	// From Löve <3
	// https://bitbucket.org/rude/love/src/4cd5ea6e847f2b6cc266e7a7490a70dc2802cbbe/src/common/runtime.cpp?at=default#cl-332
	int LuaManager::table_insert(lua_State *L, int tindex, int vindex, int pos) {
		if (tindex < 0) {
			tindex = lua_gettop(L)+1+tindex;
		}
		if (vindex < 0) {
			vindex = lua_gettop(L)+1+vindex;
		}

		if (pos == -1) {
			lua_pushvalue(L, vindex);
			lua_rawseti(L, tindex, (int) lua_objlen(L, tindex)+1);
			return 0;
		}
		else if (pos < 0) {
			pos = (int) lua_objlen(L, tindex)+1+pos;
		}

		for (int i = (int) lua_objlen(L, tindex)+1; i > pos; i--) {
			lua_rawgeti(L, tindex, i-1);
			lua_rawseti(L, tindex, i);
		}

		lua_pushvalue(L, vindex);
		lua_rawseti(L, tindex, pos);
		return 0;
	}

	void LuaManager::doString(const std::string & string){
		getDefault().internalDoString(string);
	}

	void LuaManager::addToLuaPath(const std::string & path ){
		getDefault().internalAddToLuaPath(path);
	}

	void LuaManager::addToLuaCPath(const std::string & path ){
		getDefault().internalAddToLuaCPath(path);
	}

	void LuaManager::doFile(const std::string & path){
		getDefault().internalDoFile(path);
	}

	void LuaManager::printTraceBack(lua_State *L){
		if (L == NULL) {
			L = LuaManager::getVM();
		}

		lua_getfield(L, LUA_GLOBALSINDEX, "debug");
		lua_getfield(L, -1, "traceback");
		
		lua_pushvalue(L, 1);    // pass error message
		lua_pushinteger(L, 2);  // skip this function and traceback
		lua_call(L, 0, 1);      // call debug.traceback
		const char * tb = lua_tostring(L, -1);
		if (tb == NULL) {
			PRLN("ERROR: Lua traceback is null.");
		}
		else {
			PV(tb);
		}
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
		PRLN(lua_tostring(L, -1));

		if(LuaManager::criticalError){
			// PRLN(lua_tostring(L, -1));
			// exit(1);
		}
		return 0;
	}

	//Taken from http://cc.byexamples.com/2008/11/19/lua-stack-dump-for-c/
	void LuaManager::stackdump(lua_State* l){
		if(l == NULL)l = LuaManager::getVM();
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

	void LuaManager::internalDoString(const std::string & string) {
		LuaManager::internalDoString(L, string);
	}
	void LuaManager::internalDoString(lua_State* L, const std::string & string) {
		if (L == NULL) {
			Console__error("Call to LuaManger::internalDoString without a lua_State");
			return;
		}

		lua_pushcfunction(L, LuaManager::errorHandler);
		int ret = (luaL_loadstring(L, string.c_str()) || lua_pcall(L, 0, LUA_MULTRET, -2));
		// TODO : Implement error handling/logging
//		if(ret !=0){
//			std::cout << "An error occured executing a lua string. " <<std::endl;
//			std::cout << "Error : " << lua_tostring(L, -1) << std::endl;
//		}
		lua_pop(L,1);
	}

	void LuaManager::internalDoFile(const std::string & path){
		lua_pushcfunction(L, LuaManager::errorHandler);
		lua_pushcfunction(L, LuaManager::loadfile);
		lua_pushstring(L, path.c_str());
		int error = lua_pcall(L, 1, 1, 0); // load file
		if (!error) {
			error = lua_pcall(L, 0, 0, -2);  // run the result
		}
		// TODO : Implement error handling/logging
//		if (error) {
//			std::cout << "An error occured executing the lua file: " << path <<std::endl;
//			std::cout << "Error : " << lua_tostring(L, -1) << std::endl;
//		}
		lua_pop(L,1);
	}

	std::string LuaManager::getLuaPath() {
		return getInstance().internalGetLuaPath();
	}

	std::string LuaManager::internalGetLuaPath() {
		lua_getglobal( L, "package" );
		lua_getfield( L, -1, "path" );
		std::string cur_path = lua_tostring( L, -1 );
		lua_pop( L, 1 );
		lua_pop( L, 1 );
		return cur_path;
	}

	//inspired by this answer on stackoverflow http://stackoverflow.com/a/4156038
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

	void LuaManager::internalError(const std::string & error, bool critical){
		LuaManager::criticalError = critical;
		luaL_error(L, error.c_str());
	}


}
