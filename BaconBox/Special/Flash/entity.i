
%module EntityWrapper

%{
	
	#include "BaconBox/MovieClipEntity/MovieClipEntity.h"
	#include <AS3/AS3.h>
	#include <AS3/AS3++.h>

%}


%typemap(astype) (AS3::local::var) "*";

%typemap(in) (AS3::local::var aMC) {
	AS3_GetVarxxFromVar($1, $input);
}
	
	namespace BaconBox{



		class MovieClipEntity { 
    	public:
    		MovieClipEntity();
			void setMovieClip(AS3::local::var aMC);
		};
	}