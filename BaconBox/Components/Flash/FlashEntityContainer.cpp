#include "FlashEntityContainer.h"
#include "BaconBox/Core/Entity.h"

namespace BaconBox {
	BB_ID_IMPL(EntityContainer);
	
	FlashEntityContainer::FlashEntityContainer() : Component() {
	}
	
	FlashEntityContainer::FlashEntityContainer(const FlashEntityContainer &src) : Component(src) {
	}
	
	FlashEntityContainer::~FlashEntityContainer() {
	}
	
	void FlashEntityContainer::receiveMessage(int senderID, int destID, int message, void *data) {
	}
	
	void FlashEntityContainer::addChild(Entity *newChild){

	}
	
	void FlashEntityContainer::addChildAt(Entity *newChild, int index){

	}
	
	bool FlashEntityContainer::contains(Entity *child) const {

	}
	
	Entity *FlashEntityContainer::getChildAt(int index){

	}

	const Entity *FlashEntityContainer::getChildAt(int index) const{

	}
	
	Entity *FlashEntityContainer::getChildByName(const std::string &name){

	}
	
	const Entity *FlashEntityContainer::getChildByName(const std::string &name){

	}
	
	int FlashEntityContainer::getChildIndex(Entity *child) const{

	}
	
	std::vector<Entity *> FlashEntityContainer::getObjectsUnderPoint(const Vector2 &point){

	}
	
	std::vector<const Entity *> FlashEntityContainer::getObjectsUnderPoint(const Vector2 &point) const{

	}
	
	Entity *FlashEntityContainer::removeChild(Entity *child){

	}
	
	Entity *FlashEntityContainer::removeChildAt(int index){

	}
	
	void FlashEntityContainer::removeChildren(int beginIndex, int endIndex){

	}
	
	void FlashEntityContainer::setChildIndex(Entity *child, int index){

	}
	
	void FlashEntityContainer::swapChildren(Entity *child1, Entity *child2){

	}
	
	void FlashEntityContainer::swapChildrenAt(int index1, int index2){

	}
	
	int FlashEntityContainer::getNbChildren() const{

	}
	
	Entity * FlashEntityContainer::getParent() const{
		
	}

}
