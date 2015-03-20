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
	
	void LineComponentProxy::setPatternSpacing(float patternSpacing){
		reinterpret_cast<LineComponent *>(component)->setPatternSpacing(patternSpacing);
	}
	
	void LineComponentProxy::setCrossOffset(float crossOffset){
		reinterpret_cast<LineComponent *>(component)->setCrossOffset(crossOffset);
	}
	float LineComponentProxy::getTextureHeadStartAt(int index){
		return reinterpret_cast<LineComponent *>(component)->getTextureHeadStartAt(index);
	}
	std::vector<Vector2> & LineComponentProxy::getPoints(){
		return reinterpret_cast<LineComponent *>(component)->getPoints();
	}
	void LineComponentProxy::clearPoints(){
		reinterpret_cast<LineComponent *>(component)->clearPoints();
	}
	
	int LineComponentProxy::getPointCount(){
		return reinterpret_cast<LineComponent *>(component)->getPointCount();
	}
//	float LineComponentProxy::getSegmentHeadStartAt(int index){
//		return reinterpret_cast<LineComponent *>(component)->getSegmentHeadStartAt(index);
//	}
	
//	void LineComponentProxy::setSegmentHeadStart(float segmentHeadStart){
//		reinterpret_cast<LineComponent *>(component)->setSegmentHeadStart(segmentHeadStart);
//	}
	
	void LineComponentProxy::setTextureHeadStart(float textureHeadStart){
		reinterpret_cast<LineComponent *>(component)->setTextureHeadStart(textureHeadStart);
	}


}
