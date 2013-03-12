#include "DefaultEntityContainer.h"

#include <algorithm>

#include "BaconBox/Core/Entity.h"
#include "BaconBox/Components/Timeline.h"
#include "BaconBox/Components/ComponentConnection.h"
#include "BaconBox/Components/Transform.h"
#include "BaconBox/Components/EntityContainerLooper.h"
#include "BaconBox/Components/Visibility.h"
#include "BaconBox/Console.h"

namespace BaconBox {
	DefaultEntityContainer::DefaultEntityContainer() : EntityContainer(), timeline(NULL), childrenByName(), children(), parent(NULL) {
		this->initializeConnections();
	}
	
	DefaultEntityContainer::DefaultEntityContainer(const DefaultEntityContainer &src) : EntityContainer(src), timeline(NULL), childrenByName(), children(src.children.size()) {
		this->initializeConnections();
		
		Entity *newEntity;
		
		std::map<Entity *, Entity *> copyMap;
		
		for (size_t i = 0; i < children.size(); ++i) {
			for (EntityByFrame::const_iterator j = src.children[i].begin(); j != src.children[i].end(); ++j) {
				newEntity = j->second->clone();
				copyMap.insert(std::make_pair(j->second, newEntity));
				
				this->children[i].insert(std::make_pair(j->first, newEntity));
			}
		}
		
		this->childrenByName = src.childrenByName;
		
		for (ChildMapByName::iterator i = this->childrenByName.begin(); i != this->childrenByName.end(); ++i) {
			for (EntityByFrame::iterator j = i->second.begin(); j != i->second.end(); ++j) {
				j->second = copyMap[j->second];
			}
		}
	}
	
	DefaultEntityContainer::~DefaultEntityContainer() {
		for (std::vector<std::map<Range<int>, Entity *, Range<int>::Comparator> >::iterator i = this->children.begin(); i != this->children.end(); ++i) {
			for (std::map<Range<int>, Entity *, Range<int>::Comparator>::iterator j = i->begin(); j != i->end(); ++j) {
				delete j->second;
			}
		}
	}
	
	DefaultEntityContainer &DefaultEntityContainer::operator=(const DefaultEntityContainer &src) {
		if (this != &src) {
			this->children.resize(src.children.size());
			
			Entity *newEntity;
			
			std::map<Entity *, Entity *> copyMap;
			
			for (size_t i = 0; i < children.size(); ++i) {
				for (EntityByFrame::const_iterator j = src.children[i].begin(); j != src.children[i].end(); ++j) {
					newEntity = j->second->clone();
					copyMap.insert(std::make_pair(j->second, newEntity));
					
					this->children[i].insert(std::make_pair(j->first, newEntity));
				}
			}
			
			this->childrenByName = src.childrenByName;
			
			for (ChildMapByName::iterator i = this->childrenByName.begin(); i != this->childrenByName.end(); ++i) {
				for (EntityByFrame::iterator j = i->second.begin(); j != i->second.end(); ++j) {
					j->second = copyMap[j->second];
				}
			}
		}
		
		return *this;
	}
	
	DefaultEntityContainer *DefaultEntityContainer::clone() const {
		return new DefaultEntityContainer(*this);
	}
	
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
			} else if (senderID == Timeline::ID) {
				if (message == Timeline::MESSAGE_NB_FRAMES_CHANGED) {
					this->setNbFrames(*reinterpret_cast<ValueChangedData<int> *>(data));
				}
			}
		}
	}
	
	void updateChild(Entity *child);
	
	void DefaultEntityContainer::update() {
		this->EntityContainer::update();
		
		EntityContainerLooper::forEachChildCurrentFrame(this, updateChild);
	}
	
	void updateChild(Entity *child) {
		child->update();
	}
	
	void renderChild(Entity *child);
	
	void DefaultEntityContainer::render() {
		this->EntityContainer::render();
		
		EntityContainerLooper::forEachChildCurrentFrame(this, renderChild);
	}
	
	void renderChild(Entity *child) {
		child->render();
	}
	
	Entity *DefaultEntityContainer::addChild(Entity *newChild) {
		return this->addChildAt(newChild, static_cast<int>(this->children.size()));
	}
	
	void DefaultEntityContainer::addChild(const EntityByFrame &newChild) {
		this->addChildAt(newChild, static_cast<int>(this->children.size()));
	}
	
	Entity *DefaultEntityContainer::addChildAt(Entity *newChild, int index) {
		EntityByFrame newChildEntry;
		
		newChildEntry.insert(std::make_pair(Range<int>(0, ((this->timeline) ? (std::max(this->timeline->getNbFrames() - 1, 0)) : (0))), newChild));
		
		this->addChildAt(newChildEntry, index);
		
		return newChild;
	}
	
	void DefaultEntityContainer::addChildAt(const EntityByFrame &newChild, int index) {
		// We make sure the given map's contents is valid.
		if (!newChild.empty()) {
			// We make sure all entities in the frame range map are valid.
			bool allValid = true;
			
			EntityByFrame::const_iterator i = newChild.begin();
			
			while (allValid && i != newChild.end()) {
				if (!i->second) {
					allValid = false;
				} else {
					++i;
				}
			}
			
			if (allValid) {
				EntityByFrame newChildCopy = newChild;
				EntityByFrame::iterator j = newChildCopy.begin();
				while (j != newChildCopy.end()) {
					DefaultEntityContainer * container =  reinterpret_cast<DefaultEntityContainer*>(j->second->getComponent(EntityContainer::ID));
					container->parent = getEntity();
					++j;
				}
				    

			    
				// We get an iterator pointing to the last frame range's entity.
				EntityByFrame::const_iterator last = newChildCopy.end();
				--last;
				
				// We calculate the iterator pointing to the new child's index.
				ChildArray::iterator position = this->children.begin() + index;
				
				
				// We insert the new child entity.
				position = this->children.insert(position, newChildCopy);
				
				// We check if the new child entity has a name.
				if (!last->second->getEntityName().empty()) {
					// We take note of it.
					std::pair<ChildMapByName::iterator, bool> result = this->childrenByName.insert(std::make_pair(last->second->getEntityName(), newChildCopy));
					
					// If there is already a child entity with the same name,
					// just too bad. (We at least write a message in the console)
					if (!result.second) {
						Console::print("A child entity with the same name already exists: ");
						Console::println(last->second->getEntityName());
						Console::printTrace();
					}
				}
			}
		}
	}
	
	bool DefaultEntityContainer::contains(Entity *child) const {
		return this->findChild(child) != this->children.end();
	}
	
	Entity *DefaultEntityContainer::getChildAt(int index) {
		Entity *result = NULL;
		
		if (index >= 0 && index < this->children.size()) {
			int frameIndex = this->getCurrentFrameIndex();
			
			EntityByFrame::iterator found = this->children[index].find(frameIndex);
			
			if (found != this->children[index].end()) {
				result = found->second;
			}
		}
		
		return result;
	}
	
	const Entity *DefaultEntityContainer::getChildAt(int index) const {
		const Entity *result = NULL;
		
		if (index >= 0 && index < this->children.size()) {
			int frameIndex = this->getCurrentFrameIndex();
			
			EntityByFrame::const_iterator found = this->children[index].find(frameIndex);
			
			if (found != this->children[index].end()) {
				result = found->second;
			}
		}
		
		return result;
	}
	
	Entity *DefaultEntityContainer::getChildByName(const std::string &name) {
		Entity *result = NULL;
		
		int frameIndex = this->getCurrentFrameIndex();
		
		ChildMapByName::iterator found = this->childrenByName.find(name);
		
		if (found != this->childrenByName.end()) {
			EntityByFrame::iterator childFound = found->second.find(frameIndex);
			
			if (childFound != found->second.end()) {
				result = childFound->second;
			}
		}
		
		return result;
	}
	
	const Entity *DefaultEntityContainer::getChildByName(const std::string &name) const {
		Entity *result = NULL;
		
		int frameIndex = this->getCurrentFrameIndex();
		
		ChildMapByName::const_iterator found = this->childrenByName.find(name);
		
		if (found != this->childrenByName.end()) {
			EntityByFrame::const_iterator childFound = found->second.find(frameIndex);
			
			if (childFound != found->second.end()) {
				result = childFound->second;
			}
		}
		
		return result;
	}
	
	int DefaultEntityContainer::getChildIndex(Entity *child) const {
		int result = static_cast<int>(this->findChild(child) - this->children.begin());
		
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
		ChildArray::iterator found = this->findChild(child);
		
		if (found != this->children.end()) {
			for (EntityByFrame::iterator i = found->begin(); i != found->end(); ++i) {
				if (i->second != child) {
					delete i->second;
				}
			}
			
			this->children.erase(found);
		}
		DefaultEntityContainer * container =  reinterpret_cast<DefaultEntityContainer*>(child->getComponent(EntityContainer::ID));
		container->parent = NULL;
		return child;
	}
	
	Entity *DefaultEntityContainer::removeChildAt(int index) {
		Entity *result = NULL;
		
		if (index >= 0 && index < this->children.size()) {
			result = this->children[index][this->getCurrentFrameIndex()];
			
			for (EntityByFrame::iterator i = this->children[index].begin(); i != this->children[index].end(); ++i) {
				if (i->second != result) {
					delete i->second;
				}
			}
		}
		if(result){
			DefaultEntityContainer * container =  reinterpret_cast<DefaultEntityContainer*>(result->getComponent(EntityContainer::ID));
			container->parent = NULL;  
		}
		
		return result;
	}
	
	void DefaultEntityContainer::removeChildren(int beginIndex, int endIndex) {
		Entity *lastRemoved;
		
		while (beginIndex < endIndex) {
			lastRemoved = this->removeChildAt(beginIndex);
			
			if (lastRemoved) {
				delete lastRemoved;
				++beginIndex;
			} else {
				beginIndex = endIndex;
			}
		}
	}
	
	void DefaultEntityContainer::setChildIndex(Entity *child, int index) {
		if (index >= 0 && index < this->children.size()) {
			ChildArray::iterator found = this->findChild(child);
			
			if (found != this->children.end()) {
				EntityByFrame tmp = *found;
				
				this->children.erase(found);
				
				this->children.insert(this->children.begin() + index, tmp);
			}
		}
	}
	
	void DefaultEntityContainer::swapChildren(Entity *child1, Entity *child2) {
		ChildArray::iterator found1 = this->findChild(child1);
		
		if (found1 != this->children.end()) {
			ChildArray::iterator found2 = this->findChild(child2);
			
			if (found2 != this->children.end()) {
				EntityByFrame tmp = *found1;
				*found1 = *found2;
				*found2 = tmp;
			}
		}
	}
	
	void DefaultEntityContainer::swapChildrenAt(int index1, int index2) {
		if (index1 >= 0 && index1 < this->children.size() && index2 >= 0 && index2 < this->children.size()) {
			EntityByFrame tmp = this->children[index1];
			this->children[index1] = this->children[index2];
			this->children[index2] = tmp;
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

	
	DefaultEntityContainer::ChildArray::iterator DefaultEntityContainer::findChild(Entity *child) {
		ChildArray::iterator result = this->children.end();
		
		ChildArray::iterator i = this->children.begin();
		EntityByFrame::const_iterator j;
		
		int frameIndex = this->getCurrentFrameIndex();
		
		while (i != this->children.end() && result == this->children.end()) {
			j = i->find(frameIndex);
			
			if (j != i->end() && j->second == child) {
				result = i;
			}
			else {
				++i;
			}
		}
		
		return result;
	}
	
	DefaultEntityContainer::ChildArray::const_iterator DefaultEntityContainer::findChild(const Entity *child) const {
		ChildArray::const_iterator result = this->children.end();
		
		ChildArray::const_iterator i = this->children.begin();
		EntityByFrame::const_iterator j;
		
		int frameIndex = this->getCurrentFrameIndex();
		
		while (i != this->children.end() && result == this->children.end()) {
			j = i->find(frameIndex);
			
			if (j != i->end() && j->second == child) {
				result = i;
			}
			else {
				++i;
			}
		}
		
		return result;
	}
	
	void DefaultEntityContainer::initializeConnections() {
		// We add the connections.
		this->addConnection(new ComponentConnection<Timeline>(&this->timeline));
		
		this->refreshConnections();
	}
	
	void DefaultEntityContainer::setNbFrames(const ValueChangedData<int> &data) {
		// If the number of frames decreased.
		if (data.newValue == 0 || data.newValue < data.oldValue) {
			// We decrease the frame range of all entities at the end of the
			// timeline.
			// If an entity's frame range is completely out, we delete the
			// entity.
			EntityByFrame::reverse_iterator j;
			
			for (ChildArray::iterator i = this->children.begin(); i != this->children.end(); ++i) {
				j = i->rbegin();
				
				while (j != i->rend() && j->first.max >= data.newValue) {
					if (j->first.min == 0 || j->first.min < data.newValue) {
						std::pair<Range<int>, Entity *> tmp = *j;
						
						i->erase((++j).base());
						
						tmp.first.max = std::max(data.newValue - 1, 0);
						
						i->insert(tmp);
					} else if (j->first.min >= data.newValue) {
						delete j->second;
						
						i->erase((++j).base());
					}
					
					j = i->rbegin();
				}
			}
		} else if (data.newValue > data.oldValue) {
			// The number of frames has increased.
			
			// We take all of the entities at the end of the timeline and expand
			// their frame range.
			EntityByFrame::reverse_iterator j;
			
			for (ChildArray::iterator i = this->children.begin(); i != this->children.end(); ++i) {
				// We get the last entity in the timeline.
				j = i->rbegin();
				std::pair<Range<int>, Entity *> tmp = *j;
				
				// We remove it.
				i->erase((++j).base());
				
				// We increase its frame range.
				tmp.first.max = data.newValue - 1;
				
				// We re-insert it.
				i->insert(tmp);
			}
		}
	}
	
}
