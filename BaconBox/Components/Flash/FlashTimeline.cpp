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
	    isPlayingFlag = false;
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
			isPlayingFlag = true;
		}

		void FlashTimeline::gotoAndPlay(const std::string &labelName){
			AS3::local::var args[1] = {AS3::local::internal::new_String(labelName.c_str())};
			movieClipHolder->callMethod("gotoAndPlay", 1, args);
			isPlayingFlag = true;
		}

		
		void FlashTimeline::gotoAndStop(int frame){
			AS3::local::var args[1] = {AS3::local::internal::new_int(frame+1)};
			movieClipHolder->callMethod("gotoAndStop", 1, args);
			isPlayingFlag = false;
		}

		void FlashTimeline::gotoAndStop(const std::string &labelName){
			AS3::local::var args[1] = {AS3::local::internal::new_String(labelName.c_str())};
			movieClipHolder->callMethod("gotoAndStop", 1, args);
			isPlayingFlag = false;
		}
		
		void FlashTimeline::nextFrame(){
			movieClipHolder->callMethod("nextFrame", 0, NULL);
		}
		
		void FlashTimeline::prevFrame(){
			movieClipHolder->callMethod("prevFrame", 0, NULL);
		}
		
		void FlashTimeline::play(){
			movieClipHolder->callMethod("play", 0, NULL);
			isPlayingFlag = true;
		}
		
		void FlashTimeline::stop(){
			movieClipHolder->callMethod("stop", 0, NULL);
			isPlayingFlag = false;
		}
		
		int FlashTimeline::getCurrentFrame() const{
			AS3::local::var currentFrame = movieClipHolder->getProperty("currentFrame");
			return AS3::local::internal::int_valueOf(currentFrame) - 1;
		}
		
		bool FlashTimeline::isPlaying() const{
			return isPlayingFlag;
		}
		
		int FlashTimeline::getNbFrames() const{
			AS3::local::var nbFrames = movieClipHolder->getProperty("totalFrames");
			return AS3::local::internal::int_valueOf(nbFrames);
		}
	
}
