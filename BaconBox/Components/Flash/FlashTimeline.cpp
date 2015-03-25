#include "FlashTimeline.h"
#include "BaconBox/Core/Entity.h"
#include "BaconBox/Console.h"
#include "BaconBox/Components/ComponentConnection.h"

#include <AS3/AS3.h>
#include <AS3/AS3++.h>
#include "BaconBox/Helper/Flash/FlashHelper.h"

namespace BaconBox {
	


	FlashTimeline::FlashTimeline() : Timeline() {
	    initializeConnections();
	}
	
	FlashTimeline::FlashTimeline(const FlashTimeline &src) : Timeline(src) {
	}
	
	FlashTimeline::~FlashTimeline() {
	}

	void FlashTimeline::initializeConnections(){
	    this->addConnection(new ComponentConnection<MovieClipHolder>(&this->movieClipHolder));
	}
	
	void FlashTimeline::receiveMessage(int senderID, int destID, int message, void *data) {
		this->Timeline::receiveMessage(senderID, destID, message, data);
	}
	
		void FlashTimeline::gotoAndPlay(int frame){
			AS3::local::var args[1] = {AS3::local::internal::new_int(frame+1)};
			movieClipHolder->callMethod("gotoAndPlay", 1, args);
		}

		void FlashTimeline::gotoAndPlay(const std::string &labelName){
			AS3::local::var args[1] = {AS3::local::internal::new_String(labelName.c_str())};
			movieClipHolder->callMethod("gotoAndPlay", 1, args);
		}

		
		void FlashTimeline::gotoAndStop(int frame){
			AS3::local::var args[1] = {AS3::local::internal::new_int(frame+1)};
			movieClipHolder->callMethod("gotoAndStop", 1, args);
		}

		void FlashTimeline::gotoAndStop(const std::string &labelName){
			AS3::local::var args[1] = {AS3::local::internal::new_String(labelName.c_str())};
			movieClipHolder->callMethod("gotoAndStop", 1, args);
		}
		
		void FlashTimeline::nextFrame(){
			movieClipHolder->callMethod("nextFrame", 0, NULL);
		}
		
		void FlashTimeline::prevFrame(){
			movieClipHolder->callMethod("prevFrame", 0, NULL);
		}
		
		void FlashTimeline::play(){
			movieClipHolder->callMethod("play", 0, NULL);
		}
		
		void FlashTimeline::stop(){
			movieClipHolder->callMethod("stop", 0, NULL);
		}
		
		int FlashTimeline::getCurrentFrame() const{
			AS3::local::var currentFrame = movieClipHolder->getProperty("currentFrame");
			return AS3::local::internal::int_valueOf(currentFrame) - 1;
		}
		
		bool FlashTimeline::isPlaying() const{
			return bool_valueOf(movieClipHolder->getProperty("isPlaying"));
		}
		
		int FlashTimeline::getNbFrames() const{
			AS3::local::var nbFrames = movieClipHolder->getProperty("totalFrames");
			return AS3::local::internal::int_valueOf(nbFrames);
		}

		bool FlashTimeline::hasLabel(const std::string& label) const{
			AS3_DeclareVar(ASlabel, String);
		    AS3_CopyCStringToVar(ASlabel, label.c_str(), label.length());

			AS3_DeclareVar(mc, *);
			AS3::local::var tempMC = movieClipHolder->getMovieClip();
			AS3_CopyVarxxToVar(mc, tempMC);

			bool res;

			inline_as3(
			    "import flash.display.FrameLabel;"
				"var i:int;\n"
				"var k:int = mc.currentLabels.length;\n"
				"var res:Boolean=false;\n"
				"for (i; i < k; ++i) {\n"
				"	var label:FrameLabel = mc.currentLabels[i];\n"
				"	if (label.name == ASlabel)\n"
				"		res= true;\n"
				"}\n"
			    "%0 = res\n"
		    : "=r"(res)
			);

			return res;
		}
	
}
