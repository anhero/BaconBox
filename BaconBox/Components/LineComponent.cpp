#include "LineComponent.h"
#include "BaconBox/Core/Entity.h"

namespace BaconBox {
	BB_ID_IMPL(LineComponent);

	LineComponent::LineComponent() : Component() {
	}

	LineComponent::LineComponent(const LineComponent &src) : Component(src) {
	}

	LineComponent::~LineComponent() {
	}

	void LineComponent::receiveMessage(int senderID, int destID, int message, void *data) {
		this->Component::receiveMessage(senderID, destID, message, data);
	}

	LineComponentProxy::LineComponentProxy(Entity *entity) : ComponentProxy(entity, NULL) {
	}

	void LineComponentProxy::setLineComponent(LineComponent * lineComponent){
	    component = lineComponent;
	    entity->addComponent(lineComponent);
	}
	
	void LineComponentProxy::addPoint(const Vector2 & point){
		reinterpret_cast<LineComponent *>(component)->addPoint(point);
	}
	
	Vector2 &LineComponentProxy::getPoint(int index) {
		return reinterpret_cast<LineComponent *>(component)->getPoint(index);
	}
	
	void LineComponentProxy::refreshPoints(){
		reinterpret_cast<LineComponent *>(component)->refreshPoints();
	}



}
