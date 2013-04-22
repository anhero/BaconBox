#include "DefaultTimeline.h"
#include "BaconBox/Components/DefaultEntityContainer.h"
#include "BaconBox/Console.h"
#include "BaconBox/Core/Entity.h"
#include "BaconBox/Helper/ValueChangedData.h"

namespace BaconBox {
	DefaultTimeline::DefaultTimeline() : Timeline(), playing(false), nbFrames(0), currentFrame(0), defaultEntityContainer(NULL) {
	    initializeConnections();
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
	
	void DefaultTimeline::initializeConnections() {
		// We add the connections.
		this->addConnection(new ComponentConnection<DefaultEntityContainer>(&this->defaultEntityContainer));
		this->refreshConnections();
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
		
		if (this->currentFrame+1 >= this->nbFrames) {
			setFrame(0);
		}
		else{
		   setFrame(this->currentFrame+1);
		}
	}
	
	void DefaultTimeline::prevFrame() {
		setFrame(this->currentFrame-1);
		if (this->currentFrame < 0) {
			setFrame(this->nbFrames);
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
	

		
	
	bool DefaultTimeline::isPlaying() const {
		return this->playing;
	}
	
	int DefaultTimeline::getNbFrames() const {
		return this->nbFrames;
	}
	
	void DefaultTimeline::setFrame(int frame){
	    this->currentFrame = frame;
	    defaultEntityContainer->setFrame(frame);
	}
	
	void DefaultTimeline::setNbFrames(int newNbFrames) {
		if (newNbFrames >= 0 && newNbFrames != this->nbFrames) {
			ValueChangedData<int> data(this->nbFrames, newNbFrames);
			
			this->nbFrames = newNbFrames;
			
			this->sendMessage(Entity::BROADCAST, Timeline::MESSAGE_NB_FRAMES_CHANGED, &data);
		}
	}
	
	void DefaultTimeline::gotoAndSetState(int frame, bool newPlaying) {
		if (frame >= 0 && frame < this->nbFrames) {
			this->playing = newPlaying;
			
			setFrame(frame);
		} else {
			if(newPlaying){
				Console::print("Trying to set a frame index out of range in gotoAndPlay(...): ");
			}
			else{
				Console::print("Trying to set a frame index out of range in gotoAndStop(...): ");
			}
			Console::println(frame);
		}
	}
	
	
}
