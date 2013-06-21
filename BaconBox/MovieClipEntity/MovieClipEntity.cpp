#include "MovieClipEntity.h"
#include <string>


#ifdef BB_FLASH_PLATFORM
#include "BaconBox/Components/Flash/MovieClipHolder.h"
#include "BaconBox/Components/Flash/FlashEntityContainer.h"
#include "BaconBox/Components/Flash/FlashTimeline.h"
#include "BaconBox/Components/Flash/FlashHasName.h"
#include "BaconBox/Components/Flash/FlashSizeComponent.h"
#include "BaconBox/Components/Flash/FlashTransform.h"
#include "BaconBox/Components/Flash/FlashAABBHitBox.h"
#include "BaconBox/Components/Flash/FlashColorTransform.h"
#else
#include "BaconBox/Components/Mesh.h"
#include "BaconBox/Components/MeshDriverRenderer.h"
#include "BaconBox/Components/DefaultMatrix.h"
#include "BaconBox/Components/Timeline.h"
#include "BaconBox/Components/DefaultEntityContainer.h"
#include "BaconBox/Components/DefaultTimeline.h"
#include "BaconBox/Components/DefaultAABBHitBox.h"
#endif
namespace BaconBox {

    BB_ID_IMPL(MovieClipEntity);

	MovieClipEntity::MovieClipEntity(): Entity(), HasNameProxy(this, "", false), TransformProxy(this, false), ColorTransformProxy(this), TimelineProxy(this), ClickableProxy(this), EntityContainerProxy(this), MatrixComponentProxy(this), SymbolComponentProxy(this), AABBHitBoxProxy(this), SizeComponentProxy(this)
	#ifdef BB_LUA
        , LuaEntityProxy(this)
	#endif //BB_LUA
	{

#ifdef BB_FLASH_PLATFORM
	    setTimeline(new FlashTimeline());
	    setEntityContainer(new FlashEntityContainer());
	    setHasName(new FlashHasName());
        setSizeComponent(new FlashSizeComponent());
	    setTransform(new FlashTransform());
	    setAABBHitBox(new FlashAABBHitBox());
	   setColorTransform(new FlashColorTransform());

#else
	    	    setHasName(new HasName(""));

//		    Mesh *mesh  = new Mesh();
//		    mesh->getVertices().resize(4);
//		    addComponent(mesh);
//		    this->addComponent(new MeshDriverRenderer());
	    setTimeline(new DefaultTimeline());
	    setEntityContainer(new DefaultEntityContainer());
	    setMatrixComponent(new DefaultMatrix());
	    setTransform(new Transform());
        setAABBHitBox(new DefaultAABBHitBox());
        setColorTransform(new DefaultColorTransform());
		#endif
	}

	MovieClipEntity::MovieClipEntity(const MovieClipEntity& src) : Entity(), HasNameProxy(this, ""), TransformProxy(this), ColorTransformProxy(this), TimelineProxy(this), EntityContainerProxy(this), MatrixComponentProxy(this), ClickableProxy(this),SymbolComponentProxy(this), AABBHitBoxProxy(this), SizeComponentProxy(this)
    #ifdef BB_LUA
        , LuaEntityProxy(this)
	#endif //BB_LUA
	{
#ifdef BB_FLASH_PLATFORM

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
	
	MovieClipEntity::~MovieClipEntity() {
	}

	MovieClipEntity &MovieClipEntity::operator=(const MovieClipEntity &src) {
		this->Entity::operator=(src);
		
		if (this != &src) {
		}
		
		return *this;
	}

#ifdef BB_FLASH_PLATFORM
	void MovieClipEntity::setMovieClip(AS3::local::var aMC) {
		MovieClipHolder *mcHolder = new MovieClipHolder(aMC);
		addComponent(mcHolder);

	}
#endif



}
