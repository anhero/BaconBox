#ifndef BB_ENTITYMANAGER_H
#define BB_ENTITYMANAGER_H

#include <vector>
#include <list>
#include <set>
#include "BaconBox/Core/Component.h"

namespace BaconBox {
	class EntityManager : public Component {
	public:
		BB_ID_HEADER;
		
		EntityManager();
				
		virtual ~EntityManager();
		
		void add(Entity *newEntity);
		void remove(Entity *newEntity);
								
		virtual void receiveMessage(int senderID, int destID, int message, void *data);
		
		void update();
		void render();

	private:
	    
		std::vector<Entity *> entities;
		
		std::list<Entity *> toAdd;
		
		std::set<Entity *> toRemove;

	};
}

#endif
