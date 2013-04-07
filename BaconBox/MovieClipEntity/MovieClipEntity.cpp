#include "MovieClipEntity.h"
#include <string>


#ifdef BB_FLASH_PLATEFORM
#include "BaconBox/ComponentS/Flash/MovieClipHolder.h"
#else
#include "BaconBox/Components/Mesh.h"
#include "BaconBox/Components/MeshDriverRenderer.h"
#include "BaconBox/Components/DefaultMatrix.h"
#include "BaconBox/Components/Timeline.h"
#include "BaconBox/Components/DefaultEntityContainer.h"
#include "BaconBox/Components/DefaultTimeline.h"
#endif

namespace BaconBox {
    
    BB_ID_IMPL(MovieClipEntity);
    
	MovieClipEntity::MovieClipEntity(): Entity(), HasNameProxy(this, ""), TransformProxy(this), ColorFilterProxy(this), TimelineProxy(this), EntityContainerProxy(this), MatrixComponentProxy(this), SymbolComponentProxy(this) {
	  
		#ifdef BB_FLASH_PLATEFORM

		#else
		
//		    Mesh *mesh  = new Mesh();
//		    mesh->getVertices().resize(4);
//		    addComponent(mesh);
//		    this->addComponent(new MeshDriverRenderer());
	    setTimeline(new DefaultTimeline());
	    setEntityContainer(new DefaultEntityContainer());
	    setMatrixComponent(new DefaultMatrix());
		
		#endif

	}
	
#ifdef BB_FLASH_PLATEFORM
	void MovieClipEntity::setMovieClip(AS3::local::var aMC) {
		MovieClipHolder *mcHolder = new MovieClipHolder(aMC);
		addComponent(mcHolder);    
	}
#endif
	


}
