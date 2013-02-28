#include "DefaultTimeline.h"

#include "BaconBox/Console.h"

namespace BaconBox {
	DefaultTimeline::DefaultTimeline() : Timeline(), playing(false), nbFrames(0), currentFrame(0) {
	}
	
	DefaultTimeline::DefaultTimeline(const DefaultTimeline &src) : Timeline(src), playing(src.playing), nbFrames(src.nbFrames), currentFrame(src.currentFrame) {
	}
	
	DefaultTimeline::~DefaultTimeline() {
	}
	
	DefaultTimeline &DefaultTimeline::operator=(const DefaultTimeline &src) {
		if (this != &src) {
			this->playing = src.playing;
			this->nbFrames = src.nbFrames;
			this->currentFrame = src.currentFrame;	
		}
		
		return *this;
	}
	
	DefaultTimeline *DefaultTimeline::clone() const {
		return new DefaultTimeline(*this);
	}
	
	void DefaultTimeline::receiveMessage(int senderID, int destID, int message, void *data) {
		this->Timeline::receiveMessage(senderID, destID, message, data);
	}
	
	void DefaultTimeline::update() {
		this->Timeline::update();
		
		if (this->playing) {
			this->nextFrame();
		}
	}
	
	void DefaultTimeline::gotoAndPlay(int frame) {
		this->gotoAndSetState(frame, true);
	}
	
	void DefaultTimeline::gotoAndStop(int frame) {
		this->gotoAndSetState(frame, false);
	}
	
	void DefaultTimeline::nextFrame() {
		++this->currentFrame;
		
		if (this->currentFrame < this->nbFrames) {
			this->currentFrame = 0;
		}
	}
	
	void DefaultTimeline::prevFrame() {
		--this->currentFrame;
		
		if (this->currentFrame < 0) {
			this->currentFrame = this->nbFrames;
		}
	}
	
	void DefaultTimeline::play() {
		this->playing = true;
	}
	
	void DefaultTimeline::stop() {
		this->playing = false;
	}
	
	int DefaultTimeline::getCurrentFrame() const {
		return this->currentFrame;
	}
	
	int DefaultTimeline::getNbFramesLoaded() const {
		return this->nbFrames;
	}
	
	bool DefaultTimeline::isPlaying() const {
		return this->playing;
	}
	
	int DefaultTimeline::getNbTotalFrames() const {
		return this->nbFrames;
	}
	
	void DefaultTimeline::gotoAndSetState(int frame, bool newPlaying) {
		if (frame >= 0 && frame < this->nbFrames) {
			this->playing = newPlaying;
			
			this->currentFrame = frame;
		} else {
			Console::print("Trying to set a frame index out of range in gotoAndPlay(...): ");
			Console::println(frame);
		}
	}
}
