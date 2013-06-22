#include "EmitterEntity.h"

#if !defined(BB_FLASH_PLATFORM)
#include "BaconBox/Components/DefaultTimeline.h"
#endif

namespace BaconBox {
	EmitterEntity::EmitterEntity() : MovieClipEntity(), ParticleEmitterProxy(this) {
#if !defined(BB_FLASH_PLATFORM)
		DefaultTimeline *timeline = this->getComponent<DefaultTimeline>();
		
		if (timeline) {
			timeline->setNbFrames(1);
			timeline->gotoAndStop(0);
		}
#endif
	}
	
	EmitterEntity::EmitterEntity(const EmitterEntity &src) : MovieClipEntity(src), ParticleEmitterProxy(this) {
	}
	
	EmitterEntity::~EmitterEntity() {
	}
	
	EmitterEntity &EmitterEntity::operator=(const EmitterEntity &src) {
		this->MovieClipEntity::operator=(src);
		
		if (this != &src) {
		}
		
		return *this;
	}
}
