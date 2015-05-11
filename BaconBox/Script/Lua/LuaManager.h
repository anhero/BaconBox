/**
 * @file
 * @ingroup Display
 */
#ifndef BB_LUA_MANAGER_H
#define BB_LUA_MANAGER_H

#include <string>
#include <lua.hpp>

#include "BaconBox/Core/Singleton.h"
#include "BaconBox/FileSystem/FileSystem.h"

struct lua_State;

namespace BaconBox {

	class LuaManager : public Singleton {
		BB_SINGLETON_DECL(LuaManager);
	public:

		/// Executes a string as lua code.
		static void doString(const std::string & string);
		/// Executes the specified file.
		static void doFile(const std::string & path);

		/// Adds a path to the lua package.path.
		static void addToLuaPath(const std::string & path );
		/// Adds a path to the lua package.cpath.
		static void addToLuaCPath(const std::string & path );
		/// Gets the lua package.path as a string.
		static std::string getLuaPath();

		static void error(const std::string & error, bool critical = false);

		/// Prints a lua traceback.
		static void printTraceBack(lua_State *L = NULL);
		/// Added as an error handler to handle errors.
		static int errorHandler(lua_State *L);
		/// Prints the lua stack.
		static void stackdump(lua_State* l = NULL);

		// Lua stdlib replacements/wrappers:
		/// Used to wrap print() on some platforms to output somewhere else.
		static int print(lua_State* L);
		/// Implements loadfile with the BaconBox VFS.
		static int loadfile(lua_State* L);
		/// Implements luaL_loadfile interface with the BaconBox VFS.
		static int loadfile(lua_State* L, const std::string path);
		/// Implements open with the BaconBox VFS.
		static int open(lua_State* L);
		/// Implements a 'package.loaders' for the BaconBox VFS.
		static int packageloader(lua_State* L);

		/**
		 * Do a table.insert.
		 * @param L the state
		 * @param tindex the stack index of the table
		 * @param vindex the stack index of the value
		 * @param pos the position to insert it in
		 */
		static int table_insert(lua_State *L, int tindex, int vindex, int pos);

		// FIXME : Now Default is the Singleton instance... add means to have multiple instances.
		static LuaManager& getDefault();
		static void destroyVM();
		void startVM();
		static lua_State * getVM();
		
		static bool criticalError;

	private:
		LuaManager();
		~LuaManager();

		// Internal implementations of the functions.

		/// Special implementation to be used while constructing.
		void internalDoString(lua_State* L = NULL, const std::string & string = "");
		void internalDoString(const std::string & string);
		void internalDoFile(const std::string & path);
		void internalAddToLuaPath(const std::string & path );
		void internalAddToLuaCPath(const std::string & path );
		std::string internalGetLuaPath();

		void internalError(const std::string & error, bool critical = false);

		/// Used by loadfile() to read file chunks.
		static const char* reader(lua_State* L, void* data, size_t* size);
		/// State of the reader, used by loadfile()
		struct reader_state {
			char buffer[LUAL_BUFFERSIZE];
			File* file;
			unsigned int amount_read;
			reader_state() : file(NULL), amount_read(0) {}
			~reader_state() {delete file;}
		};

		lua_State *L;

	};

}
#endif
