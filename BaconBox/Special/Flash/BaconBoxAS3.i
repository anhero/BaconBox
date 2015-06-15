
%module BaconBoxAS3

%{
	
	#include "BaconBox/MovieClipEntity/MovieClipEntity.h"
	#include <AS3/AS3.h>
	#include <AS3/AS3++.h>
	#include <iostream>
	#include "BaconBox/Core/Engine.h"
	#include "BaconBox/Console.h"
	#include "BaconBox/Display/Text/Font.h"

	#include "BaconBox/Display/Text/Flash/FlashFont.h"

	#ifdef BB_LUA
		#include "BaconBox/Script/Lua/LuaManager.h"
	#endif
    #include "BaconBox/FileSystem/FileSystem.h"

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

		


		class FlashEngine{
		public:
		FlashEngine();
		};

		
		class MovieClipEntity { 
    	public:
    		MovieClipEntity();
			void setMovieClip(AS3::local::var aMC);
		};

		class TextEntity : public MovieClipEntity { 
    	public:
    		TextEntity(Font * font);
		};

		class Engine {
			public:
			static void pulse();

			static void initializeEngine(unsigned int resolutionWidth,
		                             unsigned int resolutionHeight);


		    static void application(int argc, char *argv[]);

		};

        class FileSystem {
        public:
            static bool mount(const std::string& what, const std::string& where = "/", const bool append = false);
            static bool mountDefaultSavePath(const std::string& where = "/Save");
            static bool rawMount(const std::string& what, const std::string& where = "/", const bool write = false, const bool append = false);
        private:
            FileSystem();
        };
	}

#ifdef BB_LUA
	%include "BaconBox/Script/Lua/LuaManager.h"
#endif
