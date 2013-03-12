#ifndef BB_ENTITY_H
#define BB_ENTITY_H

#include <vector>
#include <string>

#include "Component.h"

#include <sigly.h>


namespace BaconBox {
	class Component;

	/**
	 * Represents an entity that has components.
	 */
	class Entity : public sigly::HasSlots<> {
	public:
		/// Message ID to use when broadcasting a message to all child components.
		static int BROADCAST;
		BB_ID_HEADER;
		
		static int MESSAGE_ADD_COMPONENT;
		static int MESSAGE_REMOVE_COMPONENT;
		
		/**
		 * Default constructor. Initializes an entity without any components.
		 */
		Entity();

		/**
		 * Copy constructor.
		 * @param src Entity to create a copy of.
		 */
		Entity(const Entity &src);

		/**
		 * Destructor.
		 */
		virtual ~Entity();

		/**
		 * Assignment operator overload.
		 * @param src Entity to copy.
		 * @return Reference to the current instance.
		 */
		Entity &operator=(const Entity &src);

		/**
		 * Clones the current instance.
		 */
		virtual Entity *clone() const;

		/**
		 * Sends a message to all components.
		 */
		void sendMessage(int senderID, int destID, int message, void *data);

		/**
		 * Updates all of the entity's components.
		 */
		void update();
		
		/**
		 * Calls the render method on all of the entity's components.
		 */
		void render();

		/**
		 * Gets the name of the entity's type.
		 * @return String containing the name of the entity's type.
		 */
		const std::string &getEntityName() const;

		/**
		 * Prints all of the entity's components' names.
		 */
		void printComponentsName();
		
		/**
		 * Gets all of the entity's components.
		 * @return Vector containing all of the entity's components.
		 */
		const std::vector<Component *> &getComponents() const;
		
		/**
		 * Adds a component to the entity.
		 * @return Returns the component that was added.
		 */
		Component *addComponent(Component *newComponent);
		
		/**
		 * Removes the component at the given index. Does nothing if the given
		 * index out of bounds.
		 * @param index Index of the component to remove.
		 */
		void removeComponentAt(std::vector<Component *>::size_type index);
		
		/**
		 * Removes the given component.
		 */
		void removeComponent(Component *component);
		
		/**
		 * Removes all of the components of the given type.
		 */
		void removeComponents(int id);

		/**
		 * Removes all of the entity's components.
		 */
		void clear();
		
		/**
		 * Gets the component with the given name.
		 * @param componentName Name of the type of the component to get.
		 * @return Pointer to the found component. Null if not found.
		 */
		Component *getComponent(const std::string &componentName) const ;
		
		/**
		 * Gets the component of the type of the given ID.
		 * @param id ID of the type of the component to find.
		 */
		Component *getComponent(int id) const;
	
		
	private:
		/**
		 * Frees all dynamically alocated memory.
		 */
		void free();
		
		/**
		 * Makes the current instance a copy of the given entity.
		 * @param src Entity to copy.
		 */
		void copyFrom(const Entity &src);

		/// Contains all of the entity's components.
		std::vector<Component *> components;
		
	};
}

#endif
