#ifndef BB_ENTITY_H
#define BB_ENTITY_H

#include <vector>
#include <string>

namespace BaconBox {
	class Component;
	
	/**
	 * Represents an entity that has components and can contain other entities.
	 */
	class Entity {
	public:
	private:
		std::vector<Component *> components;
		
		std::vector<Entity *> children;
		Entity *parent;
	};
}

#endif
