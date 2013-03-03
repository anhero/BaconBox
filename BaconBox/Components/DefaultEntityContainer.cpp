#include "DefaultEntityContainer.h"

#include <algorithm>

#include "BaconBox/Core/Entity.h"
#include "BaconBox/Components/Timeline.h"
#include "BaconBox/Components/ComponentConnection.h"
#include "BaconBox/Components/Transform.h"
#include "BaconBox/Components/EntityContainerLooper.h"
#include "BaconBox/Console.h"

namespace BaconBox {
	DefaultEntityContainer::DefaultEntityContainer() : EntityContainer(), timeline(NULL), childrenByName(), children() {
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
		
		if (senderID == Transform::ID && destID == Entity::BROADCAST) {
			EntityContainerLooper::forEachChild(this, SendMessageChild(senderID, destID, message, data));
		}
	}
	
	void updateChild(Entity *child);
	
	void DefaultEntityContainer::update() {
		this->EntityContainer::update();
		
		EntityContainerLooper::forEachChild(this, updateChild);
	}
	
	void updateChild(Entity *child) {
		child->update();
	}
	
	void renderChild(Entity *child);
	
	void DefaultEntityContainer::render() {
		this->EntityContainer::render();
		
		EntityContainerLooper::forEachChild(this, renderChild);
	}
	
	void renderChild(Entity *child) {
		child->render();
	}
	
	Entity *DefaultEntityContainer::addChild(Entity *newChild) {
		return this->addChildAt(newChild, static_cast<int>(this->children.size()));
	}
	
	Entity *DefaultEntityContainer::addChildAt(Entity *newChild, int index) {
		// We make sure the given new child is valid.
		if (newChild) {
			// We make sure the given index is valid.
			if (index >= 0 && index <= this->children.size()) {
				ChildArray::iterator position = this->children.begin() + index;
				
				int rangeEnd = (this->timeline) ? (std::max(this->timeline->getNbTotalFrames() - 1, 0)) : 1;
				
				position = this->children.insert(position, EntityByFrame());
				
				position->insert(std::make_pair(Range<int>(0, rangeEnd), newChild));
				
				// We check if the new child entity has a name.
				if (!newChild->getEntityName().empty()) {
					// We take note of it.
					std::pair<ChildMapByName::iterator, bool> result = this->childrenByName.insert(std::make_pair(newChild->getEntityName(), *position));
					
					// If there is already a child entity with the same name, just
					// too bad.
					if (!result.second) {
						Console::print("A child entity with the same name already exists: ");
						Console::println(newChild->getEntityName());
						Console::printTrace();
					}
				}
			}
		}
		
		return newChild;
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
			this->children.erase(found);
		}
		
		return child;
	}
	
	Entity *DefaultEntityContainer::removeChildAt(int index) {
		Entity *result = NULL;
		
		if (index >= 0 && index < this->children.size()) {
			result = this->children[index][this->getCurrentFrameIndex()];
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
		// We make sure we have the current components.
		this->Component::updateConnections();
		
		// We add the connections.
		this->addConnection(new ComponentConnection<Timeline>(&this->timeline));
	}
	
	void DefaultEntityContainer::updateConnections() {
		Entity *entity = this->getEntity();
		
		if (entity) {
			this->timeline = reinterpret_cast<Timeline *>(entity->getComponent(Timeline::ID));
		}
	}
}
