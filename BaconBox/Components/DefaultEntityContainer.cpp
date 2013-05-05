#include "DefaultEntityContainer.h"

#include <algorithm>

#include "BaconBox/Core/Entity.h"
#include "BaconBox/Components/Timeline.h"
#include "BaconBox/Components/ComponentConnection.h"
#include "BaconBox/Components/Transform.h"
#include "BaconBox/Components/EntityContainerLooper.h"
#include "BaconBox/Components/Visibility.h"
#include "BaconBox/Console.h"
#include "BaconBox/MovieClipEntity/MovieClipEntity.h"
#include "HasName.h"
#include "BaconBox/Helper/TimeHelper.h"
#include "BaconBox/Components/DefaultMatrix.h"
namespace BaconBox {
	DefaultEntityContainer::DefaultEntityContainer() : EntityContainer(), timeline(NULL), children(), parent(NULL), previousFrame(-1) {
		this->initializeConnections();
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
			for(std::deque<MovieClipEntity*>::iterator j = i->second.begin(); j != i->second.end(); j++){
				throw; //This is wrong, some entity will get deleted more than once.
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
			if(senderID == DefaultTimeline::ID && message == DefaultTimeline::MESSAGE_NB_FRAMES_CHANGED){
				setNbFrame(reinterpret_cast<ValueChangedData<int>* >(data)->newValue);
			}
		}
	}
	
	void DefaultEntityContainer::setNbFrame(int nbFrames){
		ChildArray::iterator iterator = children.begin();
		for(int i = 0; i < nbFrames; i++){
			children.insert(iterator, std::make_pair(i, std::deque<MovieClipEntity*>()));
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
	
	
	void DefaultEntityContainer::addChildToCurrentFrame(MovieClipEntity *newChild){
		addChildAt(newChild, static_cast<int>(frameIterator->second.size()), frameIterator);
	}

	
	
	void DefaultEntityContainer::addChild(MovieClipEntity *newChild) {
		for(int i = 0; i < timeline->getNbFrames(); i++){
			this->addChildAt(newChild, static_cast<int>(this->children[i].size()),  i);
		}
	}
	
	void DefaultEntityContainer::addChild(MovieClipEntity *newChild, int frame) {
		this->addChildAt(newChild, static_cast<int>(this->children[frame].size()),  frame);
	}
	
	void DefaultEntityContainer::addChildAt(MovieClipEntity *newChild, int index) {
	    if(this->timeline->getNbFrames() == 0)this->timeline->setNbFrames(1);
		for(int i = 0; i < this->timeline->getNbFrames(); i++){
		    addChildAt(newChild, index , i);
		}
	}
	
	void DefaultEntityContainer::addChildAt(MovieClipEntity *newChild, int index, ChildArray::iterator frameIterator){
		std::deque<MovieClipEntity*> & frameChildren =  frameIterator->second;
		DefaultEntityContainer * container =  reinterpret_cast<DefaultEntityContainer*>(newChild->getComponent(EntityContainer::ID));
		container->parent = reinterpret_cast<MovieClipEntity*>(getEntity());
		if(index >= frameChildren.size()){
			frameChildren.push_back(newChild);
		}
		else if(index <= 0){
			frameChildren.push_front(newChild);
		}
		else{
		    int position = 0;
		    std::deque<MovieClipEntity*>::iterator i;
		    for(i = frameChildren.begin(); i != frameChildren.end(); i++){
				if(index == position){
					break;
				}
				position++;
		    }
		    frameChildren.insert(i, newChild);
		}
	}

	
	void DefaultEntityContainer::addChildAt(MovieClipEntity *newChild, int index, int frame) {
		
		addChildAt(newChild, index, children.find(frame));
	}
	
	bool DefaultEntityContainer::contains(MovieClipEntity *child) const {
		return this->findChild(child) != frameIterator->second.end();
	}
	
	MovieClipEntity *DefaultEntityContainer::getChildAt(int index) {
		return frameIterator->second.at(index);
	}
	
	const MovieClipEntity *DefaultEntityContainer::getChildAt(int index) const {
		const MovieClipEntity *result = NULL;
		int position = 0;
		bool found = false;
		std::deque<MovieClipEntity*>::iterator i;
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
	
	MovieClipEntity *DefaultEntityContainer::getChildByName(const std::string &name) {
		MovieClipEntity *result = NULL;
		std::deque<MovieClipEntity*>::iterator i = frameIterator->second.begin();
		
		while (result == NULL && i != frameIterator->second.end()) {
		    if(static_cast<MovieClipEntity*>(*i)->getName() == name) {
				result = *i;
		    } else {
				++i;
			}
		}
		
		return result;
	}
	
	const MovieClipEntity *DefaultEntityContainer::getChildByName(const std::string &name) const {
		MovieClipEntity *result = NULL;
		std::deque<MovieClipEntity*>::const_iterator i = frameIterator->second.begin();
		
		while (result == NULL && i != frameIterator->second.end()) {
		    if(static_cast<MovieClipEntity*>(*i)->getName() == name) {
				result = *i;
		    } else {
				++i;
			}
		}
		
		return result;
	}
	
	int DefaultEntityContainer::getChildIndex(MovieClipEntity *child) const {
		int result = static_cast<int>(this->findChild(child) - frameIterator->second.begin());
		
		if (result == this->children.size()) {
			result = -1;
		}
		
		return result;
	}
	
	std::vector<MovieClipEntity *> DefaultEntityContainer::getObjectsUnderPoint(const Vector2 &point) {
		std::vector<MovieClipEntity *> result;
		
		// TODO: collision detection.
		
		return result;
	}
	
	std::vector<const MovieClipEntity *> DefaultEntityContainer::getObjectsUnderPoint(const Vector2 &point) const {
		std::vector<const MovieClipEntity *> result;
		
		// TODO: collision detection.
		
		return result;
	}
	
	MovieClipEntity *DefaultEntityContainer::removeChild(MovieClipEntity *child) {
		std::deque<MovieClipEntity*>::iterator found = this->findChild(child);
		
		if (found != frameIterator->second.end()) {
			frameIterator->second.erase(found);
		}
		DefaultEntityContainer * container =  reinterpret_cast<DefaultEntityContainer*>(child->getComponent(EntityContainer::ID));
		container->parent = NULL;
		return child;
	}
	
	
	void DefaultEntityContainer::removeAllChildren(){
	    children.clear();
	}
	
	MovieClipEntity *DefaultEntityContainer::removeChildAt(int index) {
		MovieClipEntity * entity = getChildAt(index);
		removeChild(entity);
		return entity;
	}
	
	void DefaultEntityContainer::removeChildren(int beginIndex, int endIndex) {
	    for(int i = beginIndex; i <= endIndex; i++){
			removeChildAt(i);
	    }
	}
	
	void DefaultEntityContainer::setChildIndex(MovieClipEntity *child, int index) {
		if (index >= 0 && index < frameIterator->second.size()) {
			std::deque<MovieClipEntity*>::iterator found = this->findChild(child);
			
			if (found != frameIterator->second.end()) {
				MovieClipEntity* tmp = *found;
				
				frameIterator->second.erase(found);
				
				frameIterator->second.insert(frameIterator->second.begin() + index, tmp);
			}
		}
	}
	
	void DefaultEntityContainer::swapChildren(MovieClipEntity *child1, MovieClipEntity *child2) {
		std::deque<MovieClipEntity*>::iterator found1 = this->findChild(child1);
		
		if (found1 != frameIterator->second.end()) {
			std::deque<MovieClipEntity*>::iterator found2 = this->findChild(child2);
			
			if (found2 != frameIterator->second.end()) {
				MovieClipEntity* tmp = *found1;
				*found1 = *found2;
				*found2 = tmp;
			}
		}
	}
	
	void DefaultEntityContainer::swapChildrenAt(int index1, int index2) {
		if (index1 >= 0 && index1 < this->children.size() && index2 >= 0 && index2 < this->children.size()) {
		    MovieClipEntity * entity1 = getChildAt(index1);
		    MovieClipEntity * entity2 = getChildAt(index2);
		    swapChildren(entity1, entity2);
		}
	}
	
	int DefaultEntityContainer::getNbChildren() const {
		return (children.size() == 0 ? 0 : static_cast<int>(getCurrentFrameChildren()->size()));
	}
	
	int DefaultEntityContainer::getCurrentFrameIndex() const {
		return this->timeline ? this->timeline->getCurrentFrame() : 0;
	}
	
	MovieClipEntity * DefaultEntityContainer::getParent() const{
	    return parent;
	}
	std::deque<MovieClipEntity*> * DefaultEntityContainer::getCurrentFrameChildren() const {
	    return (frameIterator != children.end() ? & frameIterator->second : NULL);
	}
	
	std::deque<MovieClipEntity*> * DefaultEntityContainer::getCurrentFrameChildren(){
	    return (frameIterator != children.end() ? & frameIterator->second : NULL);
	}
	
	void DefaultEntityContainer::setFrame(int frame){
	    frameIterator = children.find(frame);
		std::deque<MovieClipEntity*> * currentChildren =  getCurrentFrameChildren();
		if(currentChildren){
			for(std::deque<MovieClipEntity*>::iterator i = currentChildren->begin(); i != currentChildren->end(); i++){
				(*i)->getComponent<DefaultMatrix>()->setFrameMatrix(frame);
			}
		}
		else {
			children[frame];
			frameIterator = children.find(frame);
		}
	}
	
	std::deque<MovieClipEntity*>::iterator DefaultEntityContainer::findChild(MovieClipEntity *child) {
		std::deque<MovieClipEntity*>::iterator i;
		for(i = frameIterator->second.begin(); i != frameIterator->second.end(); i++){
		    if(*i == child){
				return i;
		    }
		}
		return frameIterator->second.end();
	}
	
	std::deque<MovieClipEntity*>::const_iterator DefaultEntityContainer::findChild(const MovieClipEntity *child) const {
		std::deque<MovieClipEntity*>::const_iterator i;
		for(i = frameIterator->second.begin(); i != frameIterator->second.end(); i++){
		    if(*i == child){
				return i;
		    }
		}
		return frameIterator->second.end();
	}
	
	
}
