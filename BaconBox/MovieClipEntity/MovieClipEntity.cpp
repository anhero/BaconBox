#include "MovieClipEntity.h"
#include "BaconBox/Components/Transform.h"
#include <string>
#include "BaconBox/Components/Transform.h"

namespace BaconBox {
#ifdef BB_FLASH_PLATEFORM
	MovieClipEntity::MovieClipEntity(AS3::local::var aMC):Entity(){
		MovieClipHolder * mcHolder = new MovieClipHolder(aMC);
		addComponent(mcHolder);
		
                Transform * transform = new Transform();
                addComponent(transform);
		
		
		
		bob = 0;
		
		
		AS3::local::var otherMC = ((MovieClipHolder*)getComponent("MovieClipHolder"))->getMovieCLip();
		inline_as3("import flash.display.MovieClip;\n"::);
		inline_as3("var aMovieClip;\n"::);
		AS3_CopyVarxxToVar(aMovieClip, otherMC);
		inline_as3("(aMovieClip as MovieClip).gotoAndStop(2);\n"::);

		
	}
	
//	int MovieClipEntity::getNumber(){
//
//		
//		return test;
//	}
	
	void MovieClipEntity::setMovieClip(AS3::local::var aMC){
		
		}
	
	void MovieClipEntity::tick(){
		
		bob++;
		if(bob > 200) bob = 0;
		AS3::local::var otherMC = ((MovieClipHolder*)getComponent("MovieClipHolder"))->getMovieCLip();
		inline_as3("import flash.display.MovieClip;\n"::);
		inline_as3("var aMovieClip;\n"::);
		AS3_CopyVarxxToVar(aMovieClip, otherMC);
		inline_as3("(aMovieClip as MovieClip).x = %0;\n"::"r"(bob));
		
	}
	
#else
	
	MovieClipEntity::MovieClipEntity():Entity(){
		mesh  = new Mesh();
		mesh->getVertices().resize(4);
		addComponent(mesh);
		
	}
	
	
#endif
	
	


}
