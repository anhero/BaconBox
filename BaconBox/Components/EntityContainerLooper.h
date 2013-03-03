#ifndef BB_ENTITY_CONTAINER_LOOPER_H
#define BB_ENTITY_CONTAINER_LOOPER_H

#include "BaconBox/Components/DefaultEntityContainer.h"
#include "BaconBox/Components/Timeline.h"
#include "BaconBox/Core/Entity.h"

namespace BaconBox {
	class EntityContainerLooper {
	public:
		template <typename UnaryPredicate>
		static void forEachChild(DefaultEntityContainer *container, UnaryPredicate predicate) {
			for (DefaultEntityContainer::ChildArray::iterator i = container->children.begin(); i != container->children.end(); ++i) {
				for (DefaultEntityContainer::EntityByFrame::iterator j = i->begin(); j != i->end(); ++j) {
					predicate(j->second);
				}
			}
		}
		
		template <typename UnaryPredicate>
		static void forEachChildCurrentFrame(DefaultEntityContainer *container, UnaryPredicate predicate) {
			int frameIndex = (container->timeline) ? (container->timeline->getCurrentFrame()) : (0);
			
			DefaultEntityContainer::ChildArray::value_type::iterator found;
			
			for (DefaultEntityContainer::ChildArray::iterator i = container->children.begin(); i != container->children.end(); ++i) {
				found = i->find(frameIndex);
				
				if (found != i->end()) {
					predicate(found->second);
				}
			}
		}
	};
}

#endif
