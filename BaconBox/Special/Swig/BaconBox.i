
%module BaconBox

#if defined(BB_LUA)
	%native(cast) int luacast(lua_State*L);
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
