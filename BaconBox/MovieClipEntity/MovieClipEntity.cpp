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
		
		
	}
	
	void MovieClipEntity::setMovieClip(AS3::local::var aMC){
		
		}
	
	void MovieClipEntity::tick(){
		
		bob++;
		if(bob > 200) bob = 0;
		//((Transform*)getComponent(Transform::ID))->setPosition(Vector2(200,200));
		
	}
	
#else
	
	MovieClipEntity::MovieClipEntity():Entity(){
		mesh  = new Mesh();
		mesh->getVertices().resize(4);
		addComponent(mesh);
		
	}
	
	
#endif
	
	


}
