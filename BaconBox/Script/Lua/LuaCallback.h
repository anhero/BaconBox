
#ifndef BB_LUACALLBACK_H
#define BB_LUACALLBACK_H
#include "sigly.h"
#include "BaconBox/Console.h"

struct swig_type_info;
struct lua_State;
namespace BaconBox {
	
	class LuaCallback : public sigly::HasSlots<sigly::SingleThreaded> {
	public:
		LuaCallback(lua_State * L, const std::string & type = "");
		void call();
		void call(void* param);
	private:
		lua_State * L;
		int table_index;
		int function_index;
		
		swig_type_info* swigType1;
		
		static int EMPTY_LUA_REF;
	};
	
}

#endif
