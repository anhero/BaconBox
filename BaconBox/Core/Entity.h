#ifndef BB_ENTITY_H
#define BB_ENTITY_H

#include <vector>
#include <string>

#include "Component.h"

namespace BaconBox {
	class Component;

	/**
	 * Represents an entity that has components and can contain other entities.
	 */
	class Entity {
	public:
		Entity();

		Entity(const Entity &src);

		~Entity();

		Entity &operator=(const Entity &src);

		virtual Entity *clone() const;

		void sendMessage(int id, int message, void *data);

		void update();
		void render();

		const std::string &getName() const;
		void setName(const std::string &newName);

		template <typename T>
		T *getComponent(const std::string &componentName) const {
			T *result = NULL;
			bool notFound = true;
			std::vector<Component *>::const_iterator i = this->components.begin();

			while (notFound && i != this->components.end()) {
				if ((*i)->getId() == ID<T>::NUMBER && (*i)->getName() == componentName) {
					result = reinterpret_cast<T *>(*i);
					notFound = false;
				}
			}

			return result;
		}

		template <typename T>
		T *getComponent() const {
			T *result = NULL;
			bool notFound = true;
			std::vector<Component *>::const_iterator i = this->components.begin();

			while (notFound && i != this->components.end()) {
				if ((*i)->getId() == ID<T>::NUMBER) {
					result = reinterpret_cast<T *>(*i);
					notFound = false;
				}
			}

			return result;
		}

		const std::vector<Component *> &getComponents() const;
		void addComponent(Component *newComponent);
		void removeComponentAt(std::vector<Component *>::size_type index);
		void removeComponent(Component *component);
		void removeComponents(int id);

		const std::vector<Entity *> &getChildren() const;
		void addChild(Entity *newChild);
		void removeChildAt(std::vector<Entity *>::size_type index);
		void removeChild(Entity *child);

		void clear();
	private:
		void free();
		void copyFrom(const Entity &src);

		std::string name;
		std::vector<Component *> components;
		std::vector<Entity *> children;
		Entity *parent;
	};
}

#endif
