#include "MovieClipHolder.h"

namespace BaconBox {
	
	MovieClipHolder::MovieClipHolder(AS3::local::var aMC) : Component(){
		setName("MovieClipHolder");
		setMovieClip(aMC);
	}
	
	void MovieClipHolder::setMovieClip(AS3::local::var aMC){
		mc = aMC;
	}
	
	AS3::local::var MovieClipHolder::getMovieCLip(){
		return mc;
	}
    
}