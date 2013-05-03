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
				for (std::deque<MovieClipEntity*>::iterator j = i->second.begin(); j != i->second.end(); ++j) {
					predicate(*j);
				}
			}
		}
		
		template <typename UnaryPredicate>
		static void forEachChildCurrentFrame(DefaultEntityContainer *container, UnaryPredicate predicate) {
			std::deque<MovieClipEntity*> * currentChildren =  container->getCurrentFrameChildren();
			if(currentChildren){
			    std::deque<MovieClipEntity*>::iterator i;
			    for(i = currentChildren->begin(); i != currentChildren->end(); i++){
				    predicate(*i);
			    }
			}
		}
	};
}

#endif
