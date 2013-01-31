
%module BaconBoxAS3

%{
	
	#include "BaconBox/MovieClipEntity/MovieClipEntity.h"
	#include <AS3/AS3.h>
	#include <AS3/AS3++.h>

	#ifdef BB_LUA
		#include "BaconBox/Script/Lua/LuaManager.h"
	#endif


%}


%typemap(astype) (AS3::local::var) "*";

%typemap(in) (AS3::local::var aMC) {
	AS3_GetVarxxFromVar($1, $input);
}


%typemap(astype) std::string& "String";
%typemap(in) (std::string&) (std::string temp) {
	char *str = NULL;
	AS3_MallocString(str, $input);
	temp.assign(str);
	free(str);
	$1=&temp;
}

	
	namespace BaconBox{



		class MovieClipEntity { 
    	public:
    		MovieClipEntity();
			void setMovieClip(AS3::local::var aMC);
		};
	}

#ifdef BB_LUA
	%include "BaconBox/Script/Lua/LuaManager.h"
#endif
