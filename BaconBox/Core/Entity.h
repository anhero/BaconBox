#ifndef BB_ENTITY_H
#define BB_ENTITY_H

#include <vector>
#include <string>

#include "Component.h"

#include <sigly.h>


namespace BaconBox {
	class Component;

	/**
	 * Represents an entity that has components and can contain other entities.
	 */
	class Entity : public sigly::HasSlots<> {
	public:
                static int BROADCAST;
		BB_ID_HEADER;
                
		Entity();

		Entity(const Entity &src);

		~Entity();

		Entity &operator=(const Entity &src);

		virtual Entity *clone() const;

		void sendMessage(int senderID, int destID, int message, void *data);

		void update();
		void render();

		std::string getEntityName() const;

		void printComponentsName();
		const std::vector<Component *> &getComponents() const;
		Component * addComponent(Component *newComponent);
		void removeComponentAt(std::vector<Component *>::size_type index);
		void removeComponent(Component *component);
		void removeComponents(int id);

		void clear();
		
		Component * getComponent(const std::string &componentName) const ;
		Component * getComponent(int id) const ;
	
	private:
		void free();
		void copyFrom(const Entity &src);

		std::vector<Component *> components;
		Entity *parent;
	};
}

#endif
