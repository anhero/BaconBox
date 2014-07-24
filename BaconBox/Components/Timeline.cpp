#include "Timeline.h"
#include "BaconBox/Core/Entity.h"
namespace BaconBox {
	BB_ID_IMPL(Timeline);
	int Timeline::MESSAGE_NB_FRAMES_CHANGED = IDManager::generateID();

	Timeline::Timeline() : Component() {
	}

	Timeline::Timeline(const Timeline &src) : Component(src) {
	}

	Timeline::~Timeline() {
	}

	void Timeline::receiveMessage(int senderID, int destID, int message, void *data) {
		this->Component::receiveMessage(senderID, destID, message, data);
	}

	TimelineProxy::TimelineProxy(Entity *entity) : ComponentProxy(entity, NULL) {
	}

	void TimelineProxy::setTimeline(Timeline * timeline){
	    component = timeline;
	    entity->addComponent(timeline);
	}

	void TimelineProxy::gotoAndPlay(int frame) {
		reinterpret_cast<Timeline*>(this->component)->gotoAndPlay(frame);
	}
	void TimelineProxy::gotoAndPlay(const std::string &newName) {
		reinterpret_cast<Timeline*>(this->component)->gotoAndPlay(newName);
	}

    void TimelineProxy::gotoAndStop(int frame) {
		reinterpret_cast<Timeline*>(this->component)->gotoAndStop(frame);
	}

	void TimelineProxy::gotoAndStop(const std::string &newName) {
		reinterpret_cast<Timeline*>(this->component)->gotoAndStop(newName);
	}

	void TimelineProxy::nextFrame() {
		reinterpret_cast<Timeline*>(this->component)->nextFrame();
	}

	void TimelineProxy::prevFrame() {
		reinterpret_cast<Timeline*>(this->component)->prevFrame();
	}

	void TimelineProxy::play() {
		reinterpret_cast<Timeline*>(this->component)->play();
	}

	void TimelineProxy::stop() {
		reinterpret_cast<Timeline*>(this->component)->stop();
	}

	int TimelineProxy::getCurrentFrame() const {
		return reinterpret_cast<Timeline*>(this->component)->getCurrentFrame();
	}

	bool TimelineProxy::isPlaying() const {
		return reinterpret_cast<Timeline*>(this->component)->isPlaying();
	}

	int TimelineProxy::getNbFrames() const {
		return reinterpret_cast<Timeline*>(this->component)->getNbFrames();
	}

	bool TimelineProxy::hasLabel(const std::string& label) const{
		return reinterpret_cast<Timeline*>(this->component)->hasLabel(label);
	}

}
