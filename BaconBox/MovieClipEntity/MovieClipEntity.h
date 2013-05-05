/**
 * @file
 */
#ifndef BB_MOVIECLIPENTITY_H
#define BB_MOVIECLIPENTITY_H

#include "BaconBox/Core/Entity.h"
#include "BaconBox/PlatformFlagger.h"

#include "BaconBox/Components/Transform.h"
#include "BaconBox/Components/ColorFilter.h"
#include "BaconBox/Components/Timeline.h"
#include "BaconBox/Components/EntityContainer.h"
#include "BaconBox/Components/MatrixComponent.h"
#include "BaconBox/Components/SymbolComponent.h"
#include "BaconBox/Components/HasName.h"
#ifdef BB_FLASH_PLATEFORM
#include <AS3/AS3.h>
#include <AS3/AS3++.h>
#endif

namespace BaconBox {
	/**
	 *
	 */
	class MovieClipEntity : public Entity, public HasNameProxy, public TransformProxy, public ColorFilterProxy, public TimelineProxy, public EntityContainerProxy, public MatrixComponentProxy, public SymbolComponentProxy  {
    public:
		BB_ID_HEADER;
		
		MovieClipEntity();
		MovieClipEntity(const MovieClipEntity& src);
		
#ifdef BB_FLASH_PLATEFORM
		virtual void setMovieClip(AS3::local::var aMC);
#endif
		
		
		
    private:
		
		
	};
}

#endif // BB_MOVIECLIPENTITY_H
