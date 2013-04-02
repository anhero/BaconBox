#include "DefaultEntityContainer.h"

#include <algorithm>

#include "BaconBox/Core/Entity.h"
#include "BaconBox/Components/Timeline.h"
#include "BaconBox/Components/ComponentConnection.h"
#include "BaconBox/Components/Transform.h"
#include "BaconBox/Components/EntityContainerLooper.h"
#include "BaconBox/Components/Visibility.h"
#include "BaconBox/Console.h"
#include "MovieClipEntity/MovieClipEntity.h"
#include "HasName.h"
#include "Helper/TimeHelper.h"
#include "BaconBox/Components/DefaultMatrix.h"
namespace BaconBox {
	DefaultEntityContainer::DefaultEntityContainer() : EntityContainer(), timeline(NULL), children(), parent(NULL), previousFrame(-1) {
		this->initializeConnections();
		children[0];
		frameIterator = children.begin();
		
	}
	
	void DefaultEntityContainer::initializeConnections() {
		// We add the connections.
		this->addConnection(new ComponentConnection<DefaultTimeline>(&this->timeline));
		this->refreshConnections();
	}
	
//	DefaultEntityContainer::DefaultEntityContainer(const DefaultEntityContainer &src) : EntityContainer(src), timeline(NULL), childrenByName(), children() {
//		this->initializeConnections();
//		
//		Entity *newEntity;
//		
//		std::map<Entity *, Entity *> copyMap;
//		
//		for (size_t i = 0; i < children.size(); ++i) {
//			for (EntityByFrame::const_iterator j = src.children[i].begin(); j != src.children[i].end(); ++j) {
//				newEntity = j->second->clone();
//				copyMap.insert(std::make_pair(j->second, newEntity));
//				
//				this->children[i].insert(std::make_pair(j->first, newEntity));
//			}
//		}
//		
//		this->childrenByName = src.childrenByName;
//		
//		for (ChildMapByName::iterator i = this->childrenByName.begin(); i != this->childrenByName.end(); ++i) {
//			for (EntityByFrame::iterator j = i->second.begin(); j != i->second.end(); ++j) {
//				j->second = copyMap[j->second];
//			}
//		}
//	}
//	
	DefaultEntityContainer::~DefaultEntityContainer() {
	    for(ChildArray::iterator i = children.begin(); i != children.end(); i++){
		for(std::deque<Entity*>::iterator j = i->second.begin(); j != i->second.end(); j++){
		    delete (*j);
		}
	    }
	}
	
//	DefaultEntityContainer &DefaultEntityContainer::operator=(const DefaultEntityContainer &src) {
//		if (this != &src) {
//			this->children.resize(src.children.size());
//			
//			Entity *newEntity;
//			
//			std::map<Entity *, Entity *> copyMap;
//			
//			for (size_t i = 0; i < children.size(); ++i) {
//				for (EntityByFrame::const_iterator j = src.children[i].begin(); j != src.children[i].end(); ++j) {
//					newEntity = j->second->clone();
//					copyMap.insert(std::make_pair(j->second, newEntity));
//					
//					this->children[i].insert(std::make_pair(j->first, newEntity));
//				}
//			}
//			
//			this->childrenByName = src.childrenByName;
//			
//			for (ChildMapByName::iterator i = this->childrenByName.begin(); i != this->childrenByName.end(); ++i) {
//				for (EntityByFrame::iterator j = i->second.begin(); j != i->second.end(); ++j) {
//					j->second = copyMap[j->second];
//				}
//			}
//		}
//		
//		return *this;
//	}
	
//	DefaultEntityContainer *DefaultEntityContainer::clone() const {
//		return new DefaultEntityContainer(*this);
//	}
	
	struct SendMessageChild {
		SendMessageChild(int newSenderID, int newDestID, int newMessage, void *newData) : senderID(newSenderID), destID(newDestID), message(newMessage), data(newData) {
		}
		
		void operator() (Entity *child) {
			child->sendMessage(this->senderID, this->destID, this->message, this->data);
		}
		
		int senderID;
		int destID;
		int message;
		void *data;
	};
	
	void DefaultEntityContainer::receiveMessage(int senderID, int destID, int message, void *data) {
		this->EntityContainer::receiveMessage(senderID, destID, message, data);
		
		if (destID == Entity::BROADCAST) {
			if (senderID == Transform::ID) {
				EntityContainerLooper::forEachChild(this, SendMessageChild(senderID, destID, message, data));
			} else if (senderID == Visibility::ID) {
				EntityContainerLooper::forEachChild(this, SendMessageChild(senderID, destID, message, data));
			} 
		}
	}
	
	void updateChild(Entity *child) {
		child->update();
	}

	void renderChild(Entity *child) {
		child->render();
	}
	
	void DefaultEntityContainer::update() {
		this->EntityContainer::update();
		EntityContainerLooper::forEachChildCurrentFrame(this, updateChild);
	}
	

	
	
	void DefaultEntityContainer::render() {
		this->EntityContainer::render();
		
		EntityContainerLooper::forEachChildCurrentFrame(this, renderChild);
	}
	

	
	Entity *DefaultEntityContainer::addChild(Entity *newChild) {
		return this->addChildAt(newChild, static_cast<int>(this->children.size()));
	}
	
	void DefaultEntityContainer::addChild(const EntityByFrame &newChild) {
		this->addChildAt(newChild, static_cast<int>(this->children.size()));
	}
	
	Entity *DefaultEntityContainer::addChildAt(Entity *newChild, int index) {
		EntityByFrame newChildEntry;
		for(int i = 0; i < this->timeline->getNbFrames(); i++){
		    newChildEntry.first.insert(i);
		}
		newChildEntry.second = newChild;
		this->addChildAt(newChildEntry, index);
		
		return newChild;
	}
	
	void DefaultEntityContainer::addChildAt(const EntityByFrame &newChild, int index) {
	    for(std::set<int>::iterator i = newChild.first.begin(); i != newChild.first.end();i++){
		if(index >= children[*i].size()){
		    index = children[*i].size();
		}
		else if(index < 0){
		    index = 0;
		}
		
		    int position = 0;
		    std::deque<Entity*>::iterator j = children[*i].begin();
		    while(position != children[*i].size()){
			if(position == index){
			    break;
			}
			else{
			   j++;
			   position++; 
			}
		    }
		    DefaultEntityContainer * container =  reinterpret_cast<DefaultEntityContainer*>(newChild.second->getComponent(EntityContainer::ID));
		    container->parent = getEntity();
		    children[*i].insert(j,  newChild.second);    
		    
	    }
	}
	
	bool DefaultEntityContainer::contains(Entity *child) const {
		return this->findChild(child) != frameIterator->second.end();
	}
	
	Entity *DefaultEntityContainer::getChildAt(int index) {
		return frameIterator->second.at(index);
	}
	
	const Entity *DefaultEntityContainer::getChildAt(int index) const {
		const Entity *result = NULL;
		int position = 0;
		bool found = false;
		std::deque<Entity*>::iterator i;
		for(i = frameIterator->second.begin(); i != frameIterator->second.end(); i++){
		    if(position == index){
			found = true;
			break;
		    }
		    else{
			position++;
		    }
		}
		if(found){
		    result = *i;
		}
		return result;
	}
	
	Entity *DefaultEntityContainer::getChildByName(const std::string &name) {
		Entity *result = NULL;
		std::deque<Entity*>::iterator i;
		for(i = frameIterator->second.begin(); i != frameIterator->second.end(); i++){
		    if(static_cast<MovieClipEntity*>(*i)->getName() == name){
			return *i;
		    }
		}
	}
	
	const Entity *DefaultEntityContainer::getChildByName(const std::string &name) const {
		Entity *result = NULL;
		std::deque<Entity*>::iterator i;
		for(i = frameIterator->second.begin(); i != frameIterator->second.end(); i++){
		    if(static_cast<MovieClipEntity*>(*i)->getName() == name){
			return *i;
		    }
		}
	}
	
	int DefaultEntityContainer::getChildIndex(Entity *child) const {
		int result = static_cast<int>(this->findChild(child) - frameIterator->second.begin());
		
		if (result == this->children.size()) {
			result = -1;
		}
		
		return result;
	}
	
	std::vector<Entity *> DefaultEntityContainer::getObjectsUnderPoint(const Vector2 &point) {
		std::vector<Entity *> result;
		
		// TODO: collision detection.
		
		return result;
	}
	
	std::vector<const Entity *> DefaultEntityContainer::getObjectsUnderPoint(const Vector2 &point) const {
		std::vector<const Entity *> result;
		
		// TODO: collision detection.
		
		return result;
	}
	
	Entity *DefaultEntityContainer::removeChild(Entity *child) {
		std::deque<Entity*>::iterator found = this->findChild(child);
		
		if (found != frameIterator->second.end()) {
			frameIterator->second.erase(found);
		}
		DefaultEntityContainer * container =  reinterpret_cast<DefaultEntityContainer*>(child->getComponent(EntityContainer::ID));
		container->parent = NULL;
		return child;
	}
	
	Entity *DefaultEntityContainer::removeChildAt(int index) {
	   Entity * entity = getChildAt(index);
	   removeChild(entity);
	}
	
	void DefaultEntityContainer::removeChildren(int beginIndex, int endIndex) {
	    for(int i = beginIndex; i <= endIndex; i++){
		removeChildAt(i);
	    }
	}
	
	void DefaultEntityContainer::setChildIndex(Entity *child, int index) {
		if (index >= 0 && index < frameIterator->second.size()) {
			std::deque<Entity*>::iterator found = this->findChild(child);
			
			if (found != frameIterator->second.end()) {
				Entity* tmp = *found;
				
				frameIterator->second.erase(found);
				
				frameIterator->second.insert(frameIterator->second.begin() + index, tmp);
			}
		}
	}
	
	void DefaultEntityContainer::swapChildren(Entity *child1, Entity *child2) {
		std::deque<Entity*>::iterator found1 = this->findChild(child1);
		
		if (found1 != frameIterator->second.end()) {
			std::deque<Entity*>::iterator found2 = this->findChild(child2);
			
			if (found2 != frameIterator->second.end()) {
				Entity* tmp = *found1;
				*found1 = *found2;
				*found2 = tmp;
			}
		}
	}
	
	void DefaultEntityContainer::swapChildrenAt(int index1, int index2) {
		if (index1 >= 0 && index1 < this->children.size() && index2 >= 0 && index2 < this->children.size()) {
		    Entity * entity1 = getChildAt(index1);
		    Entity * entity2 = getChildAt(index2);
		    swapChildren(entity1, entity2);
		}
	}
	
	int DefaultEntityContainer::getNbChildren() const {
		return static_cast<int>(this->children.size());
	}
	
	int DefaultEntityContainer::getCurrentFrameIndex() const {
		return this->timeline ? this->timeline->getCurrentFrame() : 0;
	}
	
	Entity * DefaultEntityContainer::getParent() const{
	    return parent;
	}
	
	std::deque<Entity*> & DefaultEntityContainer::getCurrentFrameChild(){
	    return frameIterator->second;
	}
	
	void DefaultEntityContainer::setFrame(int frame){
	  std::deque<Entity*> & currentChildren =  getCurrentFrameChild();
	  for(std::deque<Entity*>::iterator i = currentChildren.begin(); i != currentChildren.end(); i++){
	      DefaultMatrix* test =(*i)->getComponent<DefaultMatrix>();
		test->setFrameMatrix(frame);
	  }
	}

	
	

			
	std::deque<Entity*>::iterator DefaultEntityContainer::findChild(Entity *child) {
		std::deque<Entity*>::iterator i;
		for(i = frameIterator->second.begin(); i != frameIterator->second.end(); i++){
		    if(*i == child){
			return i;
		    }
		}
		return frameIterator->second.end();
	}
	
	std::deque<Entity*>::const_iterator DefaultEntityContainer::findChild(const Entity *child) const {
		std::deque<Entity*>::const_iterator i;
		for(i = frameIterator->second.begin(); i != frameIterator->second.end(); i++){
		    if(*i == child){
			return i;
		    }
		}
		return frameIterator->second.end();
	}
	
	
}
