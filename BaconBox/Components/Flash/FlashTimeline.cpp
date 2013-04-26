#include "FlashTimeline.h"
#include "BaconBox/Core/Entity.h"
namespace BaconBox {
	
	FlashTimeline::FlashTimeline() : Timeline() {
	}
	
	FlashTimeline::FlashTimeline(const FlashTimeline &src) : Timeline(src) {
	}
	
	FlashTimeline::~FlashTimeline() {
	}
	
	void FlashTimeline::receiveMessage(int senderID, int destID, int message, void *data) {
		this->Timeline::receiveMessage(senderID, destID, message, data);
	}
	
		void FlashTimeline::gotoAndPlay(int frame){

		}
		
		void FlashTimeline::gotoAndStop(int frame){

		}
		
		void FlashTimeline::nextFrame(){

		}
		
		void FlashTimeline::prevFrame(){

		}
		
		void FlashTimeline::play(){

		}
		
		void FlashTimeline::stop(){

		}
		
		int FlashTimeline::getCurrentFrame() const{

		}
		
		bool FlashTimeline::isPlaying() const{

		}
		
		int FlashTimeline::getNbFrames() const{

		}
	
}
