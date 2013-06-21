#include "FlashTransform.h"

#include <AS3/AS3.h>
#include <AS3/AS3++.h>
#include "BaconBox/Console.h"
namespace BaconBox {
	 
	FlashTransform::FlashTransform(): Transform(), movieClipHolder(NULL), customPosition(false) {
	    initializeConnections();
	}

	const Vector2 &FlashTransform::getPosition() const {
		if (this->customPosition) {
			return this->position;
		} else {

			AS3_DeclareVar(mc, *);
			AS3::local::var tempMC = movieClipHolder->getMovieClip();
			AS3_CopyVarxxToVar(mc, tempMC);
			inline_as3(
				 "%0 = mc.x;\n"
				 "%1 = mc.y;\n"
				: "=r"(const_cast<FlashTransform*>(this)->position.x), "=r"(const_cast<FlashTransform*>(this)->position.y) :
			);
			return position;
		}
	}


	const Vector2 &FlashTransform::getRealPosition() {
		inline_as3("import flash.geom.Point");
		const_cast<FlashTransform*>(this)->realPosition = this->getPosition();
		AS3_DeclareVar(pos, flash.geom.Point);
		AS3_DeclareVar(mc, *);
		AS3::local::var tempMC = movieClipHolder->getMovieClip();
		AS3_CopyVarxxToVar(mc, tempMC);
		inline_as3(
			"pos = new Point();\n"
			"pos = mc.localToGlobal(pos);\n"
			"%0 = pos.x;\n"
			"%1 = pos.y;\n"
			: "=r"(const_cast<FlashTransform*>(this)->realPosition.x), "=r"(const_cast<FlashTransform*>(this)->realPosition.y) : 
		);

		return realPosition;
	}

	void FlashTransform::setPosition(const Vector2 &newPosition, bool withMessage) {
		this->customPosition = true;
		this->Transform::setPosition(newPosition, withMessage);
	}

	void FlashTransform::initializeConnections() {
		this->addConnection(new ComponentConnection<MovieClipHolder>(&this->movieClipHolder));
		this->refreshConnections();
	}
}
