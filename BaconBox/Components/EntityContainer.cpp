#include "EntityContainer.h"
#include "BaconBox/Core/Entity.h"

namespace BaconBox {
	BB_ID_IMPL(EntityContainer);
	
	EntityContainer::EntityContainer() : Component() {
	}
	
	EntityContainer::EntityContainer(const EntityContainer &src) : Component(src) {
	}
	
	EntityContainer::~EntityContainer() {
	}
	
	void EntityContainer::receiveMessage(int senderID, int destID, int message, void *data) {
	}
	
	
	EntityContainerProxy::EntityContainerProxy(Entity *entity) : ComponentProxy(entity, NULL) {
	}
	
	void EntityContainerProxy::setEntityContainer(EntityContainer * entityContainer){
	    component = entityContainer;
	    entity->addComponent(entityContainer);
	}

	
	void EntityContainerProxy::addChild(Entity *newChild) {
		reinterpret_cast<EntityContainer*>(this->component)->addChild(newChild);
	}
	
	void EntityContainerProxy::addChildAt(Entity *newChild, int index) {
		reinterpret_cast<EntityContainer*>(this->component)->addChildAt(newChild, index);
	}
	
	bool EntityContainerProxy::contains(Entity *child) const {
		return reinterpret_cast<const EntityContainer*>(this->component)->contains(child);
	}
	
	Entity *EntityContainerProxy::getChildAt(int index) {
		return reinterpret_cast<EntityContainer*>(this->component)->getChildAt(index);
	}
	
	const Entity *EntityContainerProxy::getChildAt(int index) const {
		return reinterpret_cast<const EntityContainer*>(this->component)->getChildAt(index);
	}
	
	Entity *EntityContainerProxy::getChildByName(const std::string &name) {
		return reinterpret_cast<EntityContainer*>(this->component)->getChildByName(name);
	}
	
	const Entity *EntityContainerProxy::getChildByName(const std::string &name) const {
		return reinterpret_cast<const EntityContainer*>(this->component)->getChildByName(name);
	}
	
	int EntityContainerProxy::getChildIndex(Entity *child) const {
		return reinterpret_cast<EntityContainer*>(this->component)->getChildIndex(child);
	}
	
	std::vector<Entity *> EntityContainerProxy::getObjectsUnderPoint(const Vector2 &point) {
		return reinterpret_cast<EntityContainer*>(this->component)->getObjectsUnderPoint(point);
	}
	
	std::vector<const Entity *> EntityContainerProxy::getObjectsUnderPoint(const Vector2 &point) const {
		return reinterpret_cast<const EntityContainer*>(this->component)->getObjectsUnderPoint(point);
	}
	
	Entity *EntityContainerProxy::removeChild(Entity *child) {
		return reinterpret_cast<EntityContainer*>(this->component)->removeChild(child);
	}
	
	Entity *EntityContainerProxy::removeChildAt(int index) {
		return reinterpret_cast<EntityContainer*>(this->component)->removeChildAt(index);
	}
	
	void EntityContainerProxy::removeChildren(int beginIndex, int endIndex) {
		reinterpret_cast<EntityContainer*>(this->component)->removeChildren(beginIndex, endIndex);
	}
	
	void EntityContainerProxy::setChildIndex(Entity *child, int index) {
		reinterpret_cast<EntityContainer*>(this->component)->setChildIndex(child, index);
	}
	
	void EntityContainerProxy::swapChildren(Entity *child1, Entity *child2) {
		reinterpret_cast<EntityContainer*>(this->component)->swapChildren(child1, child2);
	}
	
	void EntityContainerProxy::swapChildrenAt(int index1, int index2) {
		reinterpret_cast<EntityContainer*>(this->component)->swapChildrenAt(index1, index2);
	}

	int EntityContainerProxy::getNbChildren() const {
		return reinterpret_cast<const EntityContainer*>(this->component)->getNbChildren();
	}
	
	Entity * EntityContainerProxy::getParent() const{
		return reinterpret_cast<const EntityContainer*>(this->component)->getParent();
	}

}
