/**
 * @file
 */
#ifndef BB_MOVIECLIPENTITY_H
#define BB_MOVIECLIPENTITY_H

#include "BaconBox/Core/Entity.h"
#include "BaconBox/PlatformFlagger.h"

#include "BaconBox/Components/Clickable.h"

#include "BaconBox/Components/Transform.h"
#include "BaconBox/Components/ColorTransform.h"
#include "BaconBox/Components/Timeline.h"
#include "BaconBox/Components/EntityContainer.h"
#include "BaconBox/Components/MatrixComponent.h"
#include "BaconBox/Components/SymbolComponent.h"
#include "BaconBox/Components/SizeComponent.h"

#include "BaconBox/Components/AABBHitBox.h"
#include "BaconBox/Components/HasName.h"

#ifdef BB_LUA
#include "BaconBox/Components/Lua/LuaEntity.h"
#endif

#ifdef BB_FLASH_PLATFORM
#include <AS3/AS3.h>
#include <AS3/AS3++.h>
#endif

namespace BaconBox {
	/**
	 *
	 */
	class ClickableProxy;
	class MovieClipEntity : public Entity, public HasNameProxy, public TransformProxy, public ColorTransformProxy, public TimelineProxy,
	public EntityContainerProxy, public MatrixComponentProxy, public SymbolComponentProxy, public AABBHitBoxProxy, public ClickableProxy, public SizeComponentProxy
	#ifdef BB_LUA
        , public LuaEntityProxy
    #endif //BB_LUA
    {
    public:
		BB_ID_HEADER;

		MovieClipEntity();
		MovieClipEntity(const MovieClipEntity& src);
		
		virtual ~MovieClipEntity();
		
		MovieClipEntity &operator=(const MovieClipEntity &src);

#ifdef BB_FLASH_PLATFORM
		virtual void setMovieClip(AS3::local::var aMC);
#endif



    private:


	};
}

#endif // BB_MOVIECLIPENTITY_H
