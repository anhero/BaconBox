#include "MovieClipEntity.h"
#include <string>


namespace BaconBox {
#ifdef BB_FLASH_PLATEFORM
	MovieClipEntity::MovieClipEntity(AS3::local::var aMC):Entity(){
		test = 1;
		MovieClipHolder * mcHolder = new MovieClipHolder(aMC);
		addComponent(mcHolder);
		
	}
	
//	int MovieClipEntity::getNumber(){
//
//		AS3::local::var aMC = ((MovieClipHolder*)getComponent("MovieClipHolder"))->getMovieCLip();
//		inline_as3("import flash.display.MovieClip;\n"::);
//		inline_as3("var aMovieClip;\n"::);
//		AS3_CopyVarxxToVar(aMovieClip, aMC);
//		inline_as3("(aMovieClip as MovieClip).gotoAndStop(2);\n"::);
//		
//		return test;
//	}
	
	void MovieClipEntity::setMovieClip(AS3::local::var aMC){
		
		}
	
#else
	
	MovieClipEntity::MovieClipEntity():Entity(){
		mesh  = new Mesh();
		mesh->GetVertices().resize(4);
		addComponent(mesh);
		
	}
	
	
#endif
	
	


}