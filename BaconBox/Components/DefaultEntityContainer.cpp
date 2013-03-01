#include "DefaultEntityContainer.h"

#include "BaconBox/Core/Entity.h"
#include "BaconBox/Components/Timeline.h"
#include "BaconBox/Components/ComponentConnection.h"

namespace BaconBox {
	DefaultEntityContainer::DefaultEntityContainer() : EntityContainer(), timeline(NULL), childrenByName(), children() {
		this->initializeConnections();
	}
	
	DefaultEntityContainer::DefaultEntityContainer(const DefaultEntityContainer &src) : EntityContainer(src), timeline(NULL), childrenByName(), children(src.children.size()) {
		this->initializeConnections();

		Entity *newEntity;
		
		for (size_t i = 0; i < children.size(); ++i) {
			for (std::map<Range<int>, Entity *, Range<int>::Comparator>::const_iterator j = src.children[i].begin(); j != src.children[i].end(); ++j) {
				newEntity = j->second->clone();
				this->children[i].insert(std::make_pair(j->first, newEntity));
				
				if (!newEntity->getEntityName().empty()) {
					this->childrenByName.insert(std::make_pair(newEntity->getEntityName(), newEntity));
				}
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
			this->childrenByName.clear();
			
			this->children.resize(src.children.size());
			
			Entity *newEntity;
			
			for (size_t i = 0; i < children.size(); ++i) {
				this->children[i].clear();
				
				for (std::map<Range<int>, Entity *, Range<int>::Comparator>::const_iterator j = src.children[i].begin(); j != src.children[i].end(); ++j) {
					newEntity = j->second->clone();
					this->children[i].insert(std::make_pair(j->first, newEntity));
					
					if (!newEntity->getEntityName().empty()) {
						this->childrenByName.insert(std::make_pair(newEntity->getEntityName(), newEntity));
					}
				}
			}
		}
		
		return *this;
	}
	
	DefaultEntityContainer *DefaultEntityContainer::clone() const {
		return NULL;
//		return new DefaultEntityContainer(*this);
	}
	
	void DefaultEntityContainer::receiveMessage(int senderID, int destID, int message, void *data) {
		this->EntityContainer::receiveMessage(senderID, destID, message, data);
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
