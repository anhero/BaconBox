
%module BaconBox

#if defined(BB_LUA)
	%native(cast) int luacast(lua_State*L);


%luacode {
  function class(base, init)
   local c = {}    -- a new class instance
   if not init and type(base) == 'function' then
      init = base
      base = nil
   elseif type(base) == 'table' then
    -- our new class is a shallow copy of the base class!
      for i,v in pairs(base) do
         c[i] = v
      end
      c._base = base
   end
   -- the class will be the metatable for all its objects,
   -- and they will look up their methods in it.
   c.__index = c

   -- expose a constructor which can be called by <classname>(<args>)
   local mt = {}
   mt.__call = function(class_tbl, ...)
   local obj = {}
   setmetatable(obj,c)
   if class_tbl.init then
      class_tbl.init(obj,...)
   else 
      -- make sure that any stuff from the base class is initialized!
      if base and base.init then
      base.init(obj, ...)
      end
   end
   return obj
   end
   c.init = init
   c.is_a = function(self, klass)
      local m = getmetatable(self)
      while m do 
         if m == klass then return true end
         m = m._base
      end
      return false
   end
   setmetatable(c, mt)
   return c
end
}
#endif

%{
	#include "BaconBox/PlatformFlagger.h"
	#ifdef BB_FLASH_PLATEFORM
	#include <AS3/AS3.h>
	#include <AS3/AS3++.h>
	#include "BaconBox/Components/Flash/MovieClipHolder.h" 
	#endif

	#include "BaconBox/Core/Component.h"
	#include "BaconBox/Core/Entity.h"

	#include "BaconBox/Vector2.h"
	#include "BaconBox/Components/Transform.h"

	#include "BaconBox/MovieClipEntity/MovieClipEntity.h"
	#include "BaconBox/EntityFactory.h"
  #include "BaconBox/Core/State.h"

  #include "BaconBox/Core/Engine.h"
#if defined(BB_LUA)
  #include "BaconBox/Components/Lua/LuaState.h"
#endif



///////////////////////
// Helper functions
///////////////////////
#if defined(BB_LUA)
	swig_type_info * getTypeByName(lua_State* L, const char * name){
		swig_module_info* module=SWIG_GetModule(L);
		for (int i =0; i < module->size; i++){
			swig_lua_class* luaclass = (swig_lua_class*) module->types[i]->clientdata;
			if(strcmp(luaclass->name, name) ==0){
				return module->types[i];
			}
		}
		return NULL;
	}


	int luacast(lua_State*L){
		void * myDataPtr;
        void ** ptrToPtr = &myDataPtr;

        const char * type_name = luaL_checkstring(L, 2);
        swig_type_info * type = getTypeByName(L, type_name);


        SWIG_ConvertPtr(L, 1, ptrToPtr, NULL, 0);
    

        // Search the SWIG module for a swig_type_info that contains the data
        // type string that was passed as the second parameter

        if(type == NULL)
        {

                lua_pushnumber(L, -2);
                lua_pushstring(L,"Failed to find swig_type_info for specified type.");
                return 2;
        }

        // Using the swig_type_info that we found, create a new object on 
        // the stack of the desired data type and return.
        SWIG_Lua_NewPointerObj(L, myDataPtr, type, 0);

        return 1;
	}
	#endif




%}



#if defined(BB_LUA)
		%include "std_string.i"

    %typemap(arginit) (lua_State*) %{
      SWIG_ConvertPtr(L,1,(void**)&arg1,SWIGTYPE_p_BaconBox__LuaState,0);
     
    #ifdef IMPOSSIBLE_MACRO_JUST_TO_SKIP_SWIG_ARG_COUNT_CHECK_I_SHOULD_REALLY_FIND_A_FIX_IN_THE_NEAR_FUTURE
    %}
    

    %typemap(in) (lua_State*) %{ 
   #endif //IMPOSSIBLE_MACRO_JUST_TO_SKIP_SWIG_ARG_COUNT_CHECK_I_SHOULD_REALLY_FIND_A_FIX_IN_THE_NEAR_FUTURE
        
    arg2 = L;
    %}

#endif



#ifdef BB_FLASH_PLATEFORM


%typemap(astype) (AS3::local::var) "*";

%typemap(in) (AS3::local::var aMC) {
	AS3_GetVarxxFromVar($1, $input);
}



%rename("getComponentByID") getComponent(int) const;
%rename("getComponentByName") getComponent(const std::string &) const;


%ignore Component(const Component &src);
%ignore Entity(const Entity &src);
%ignore Transform(const Transform &src);


#endif




%include "BaconBox/Core/Component.h"

%include "BaconBox/Core/Entity.h"

//%include "BaconBox/Vector2.h"


namespace BaconBox{
	class Vector2{
		public:
		Vector2();
		#if defined(BB_LUA)
		Vector2(float x, float y);
		#endif

		float x;
		float y;
	};
}


%include "BaconBox/Components/Transform.h"

%include "BaconBox/MovieClipEntity/MovieClipEntity.h"

%include "BaconBox/EntityFactory.h" 

#ifdef BB_FLASH_PLATEFORM
%include "BaconBox/Components/Flash/MovieClipHolder.h"
#endif
%include "BaconBox/Core/State.h"
%include "BaconBox/Core/Engine.h"


#if defined(BB_LUA)
%include "BaconBox/Components/Lua/LuaState.h"
#endif
