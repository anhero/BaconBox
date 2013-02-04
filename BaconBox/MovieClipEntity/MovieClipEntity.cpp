#include "MovieClipEntity.h"
#include <string>


#ifdef BB_FLASH_PLATEFORM
#include "BaconBox/ComponentS/Flash/MovieClipHolder.h"
#else
#include "BaconBox/Components/Mesh.h"
#include "BaconBox/Components/MeshDriverRenderer.h"
#endif

namespace BaconBox {
    
    BB_ID_IMPL(MovieClipEntity);
    
	MovieClipEntity::MovieClipEntity(): Entity(), TransformProxy(this) {
	  
		#ifdef BB_FLASH_PLATEFORM

		#else
		
//		    Mesh *mesh  = new Mesh();
//		    mesh->getVertices().resize(4);
//		    addComponent(mesh);
//		    this->addComponent(new MeshDriverRenderer());
		
		#endif

	}
	
#ifdef BB_FLASH_PLATEFORM
	void MovieClipEntity::setMovieClip(AS3::local::var aMC) {
		MovieClipHolder *mcHolder = new MovieClipHolder(aMC);
		addComponent(mcHolder);    
	}
#endif
	


}
