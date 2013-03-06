
%module BaconBoxAS3

%{
	
	#include "BaconBox/MovieClipEntity/MovieClipEntity.h"
	#include <AS3/AS3.h>
	#include <AS3/AS3++.h>
	#include "BaconBox/Core/Engine.h"
	#include "BaconBox/Display/Text/Font.h"

	#include "BaconBox/Display/Text/Flash/FlashFont.h"

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

		class Font;
		class FlashFont : public Font{
		public:
		FlashFont(const std::string &newName = "");
		};

		class TextEntity { 
    	public:
    		TextEntity(Font * font);
			void setMovieClip(AS3::local::var aMC);
		};

		class MovieClipEntity { 
    	public:
    		MovieClipEntity();
			void setMovieClip(AS3::local::var aMC);
		};

		class Engine {
			public:
			static void pulse();

			static void initializeEngine(unsigned int resolutionWidth,
		                             unsigned int resolutionHeight);


		    static void application(int argc, char *argv[]);

		};
	}



#ifdef BB_LUA
	%include "BaconBox/Script/Lua/LuaManager.h"
#endif
