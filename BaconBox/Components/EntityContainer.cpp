#include "EntityContainer.h"
#include "BaconBox/Core/Entity.h"
#include "BaconBox/MovieClipEntity/MovieClipEntity.h"
#include "BaconBox/Core/State.h"
namespace BaconBox {
	BB_ID_IMPL(EntityContainer);

	EntityContainer::EntityContainer() : Component() {
	}

	EntityContainer::EntityContainer(const EntityContainer &src) : Component(src) {
	}

	EntityContainer::~EntityContainer() {
	}

	void EntityContainer::receiveMessage(int senderID, int destID, int message, void *data) {
	    this->Component::receiveMessage(senderID, destID, message, data);
	    if(senderID != State::ID){
            if(message == State::MESSAGE_LOST_FOCUS || message == State::MESSAGE_GET_FOCUS){
                this->propagateMessage(senderID, destID, message, data);
            }
	    }
	}


	EntityContainerProxy::EntityContainerProxy(MovieClipEntity *entity) : ComponentProxy(entity, NULL) {
	}

	void EntityContainerProxy::setEntityContainer(EntityContainer * entityContainer){
	    component = entityContainer;
	    entity->addComponent(entityContainer);
	}


	void EntityContainerProxy::addChild(MovieClipEntity *newChild) {
		reinterpret_cast<EntityContainer*>(this->component)->addChild(newChild);
	}

	void EntityContainerProxy::addChildAt(MovieClipEntity *newChild, int index) {
		reinterpret_cast<EntityContainer*>(this->component)->addChildAt(newChild, index);
	}

	bool EntityContainerProxy::contains(MovieClipEntity *child) const {
		return reinterpret_cast<const EntityContainer*>(this->component)->contains(child);
	}

	MovieClipEntity *EntityContainerProxy::getChildAt(int index) {
		return reinterpret_cast<EntityContainer*>(this->component)->getChildAt(index);
	}

	const MovieClipEntity *EntityContainerProxy::getChildAt(int index) const {
		return reinterpret_cast<const EntityContainer*>(this->component)->getChildAt(index);
	}

	MovieClipEntity *EntityContainerProxy::getChildByName(const std::string &name) {
		return reinterpret_cast<EntityContainer*>(this->component)->getChildByName(name);
	}

	const MovieClipEntity *EntityContainerProxy::getChildByName(const std::string &name) const {
		return reinterpret_cast<const EntityContainer*>(this->component)->getChildByName(name);
	}

	int EntityContainerProxy::getChildIndex(MovieClipEntity *child) const {
		return reinterpret_cast<EntityContainer*>(this->component)->getChildIndex(child);
	}

	std::vector<MovieClipEntity *> EntityContainerProxy::getObjectsUnderPoint(const Vector2 &point) {
		return reinterpret_cast<EntityContainer*>(this->component)->getObjectsUnderPoint(point);
	}

	std::vector<const MovieClipEntity *> EntityContainerProxy::getObjectsUnderPoint(const Vector2 &point) const {
		return reinterpret_cast<const EntityContainer*>(this->component)->getObjectsUnderPoint(point);
	}

	MovieClipEntity *EntityContainerProxy::removeChild(MovieClipEntity *child) {
		return reinterpret_cast<EntityContainer*>(this->component)->removeChild(child);
	}

	MovieClipEntity *EntityContainerProxy::removeChildAt(int index) {
		return reinterpret_cast<EntityContainer*>(this->component)->removeChildAt(index);
	}

	void EntityContainerProxy::removeChildren(int beginIndex, int endIndex) {
		reinterpret_cast<EntityContainer*>(this->component)->removeChildren(beginIndex, endIndex);
	}

	void EntityContainerProxy::setChildIndex(MovieClipEntity *child, int index) {
		reinterpret_cast<EntityContainer*>(this->component)->setChildIndex(child, index);
	}

	void EntityContainerProxy::swapChildren(MovieClipEntity *child1, MovieClipEntity *child2) {
		reinterpret_cast<EntityContainer*>(this->component)->swapChildren(child1, child2);
	}

	void EntityContainerProxy::swapChildrenAt(int index1, int index2) {
		reinterpret_cast<EntityContainer*>(this->component)->swapChildrenAt(index1, index2);
	}

	int EntityContainerProxy::getNbChildren() const {
		return reinterpret_cast<const EntityContainer*>(this->component)->getNbChildren();
	}

    void EntityContainerProxy::propagateMessage(int senderID, int destID, int message, void *data){
        reinterpret_cast<EntityContainer*>(this->component)->propagateMessage(senderID, destID, message, data);
	}


	MovieClipEntity * EntityContainerProxy::getParent() const{
		return reinterpret_cast<const EntityContainer*>(this->component)->getParent();
	}

}
