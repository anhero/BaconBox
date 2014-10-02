#include "FlashAABBHitBox.h"
#include "BaconBox/Core/Flash/FlashEngine.h"

namespace BaconBox {


	FlashAABBHitBox::FlashAABBHitBox(): AABBHitBox(), movieClipHolder(NULL) {
		initializeConnections();

		stage = FlashEngine::getStage();
	}

	void FlashAABBHitBox::initializeConnections() {
		this->addConnection(new ComponentConnection<MovieClipHolder>(&this->movieClipHolder));
	}

	const AABB &FlashAABBHitBox::getAABB() {
		if (!haveCustomAABB) {
			AS3_DeclareVar(mc, *);
			AS3::local::var tempMC = movieClipHolder->getMovieClip();
			AS3_CopyVarxxToVar(mc, tempMC);

			AS3_DeclareVar(stage, *);
			AS3_CopyVarxxToVar(stage, stage);

			AS3_DeclareVar(stateMC, *);
			AS3_CopyVarxxToVar(stateMC, FlashEngine::getCurrentStateMC());

			Vector2 pos;

			inline_as3(
			    "import flash.geom.Rectangle;"
			    "var bounds:Rectangle = mc.getBounds(stateMC)\n"
			    "%0 = bounds.left\n"
			    "%1 = bounds.top\n"
		    : "=r"(pos.x), "=r"(pos.y)
			);


			customAABB = AABB(pos, sizeComponent->getSize());
		}

		return customAABB;
	}

}