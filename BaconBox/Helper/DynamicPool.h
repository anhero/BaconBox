#ifndef BB_DYNAMIC_POOL_H
#define BB_DYNAMIC_POOL_H

#include <deque>

namespace BaconBox {
	/**
	 * Represents a resizable object pool. It is used to improved performance
	 * and memory use by reusing objects from a dynamic pool instead of
	 * allocating and freeing individually.
	 * @tparam T Type the pool contains.
	 */
	template <typename T>
	class DynamicPool {
	private:
		/// Represents the type of the vector that contains the objects.
		typedef std::deque<T*> ObjectContainer;
	public:
		/// Type used for counting the number of objects.
		typedef typename ObjectContainer::size_type SizeType;
		
		/**
		 * Initializes a new DynamicPool with a starting number of available
		 * objects. The number of available objects is increased when the pool
		 * runs out of available objects.
		 * @param nbAvailableObjects Starting number of available objects.
		 */
		explicit DynamicPool(SizeType nbAvailableObjects) : objects(nbAvailableObjects) {
			for (typename ObjectContainer::iterator i = this->objects.begin(); i != this->objects.end(); ++i) {
				*i = new T();
			}
		}
		
		/**
		 * Delete all remaining available objects.
		 */
		~DynamicPool() {
			for (typename ObjectContainer::iterator i = this->objects.begin(); i != this->objects.end(); ++i) {
				if (*i) {
					delete *i;
					*i = NULL;
				}
			}
		}
		
		/**
		 * Gets an available object.
		 * @return Pointer to the first available object. It may or may not
		 * be in a defaultly constructed state.
		 */
		T *create() {
			if (this->objects.empty()) {
				return new T();
			} else {
				T *result = this->objects.front();
				this->objects.pop_front();
				return result;
			}
		}
		
		/**
		 * Makes the given object available in the pool.
		 @param toFree Pointer to the item to become available.
		 */
		void free(T *toFree) {
			if (toFree) {
				this->objects.push_back(toFree);
			}
		}
		
		/**
		 * Adds the specified number of objects in the pool of available
		 * objects. Each object is created using its default constructor.
		 * @param nbToAdd Number of available objects to add to the pool.
		 */
		void addAvailableObjects(SizeType nbToAdd) {
			this->setNbAvailableObjects(this->getNbAvailableObjects() + nbToAdd);
		}
		
		/**
		 * Gets the number of objects available in the pool.
		 * @return Number of objects available in the pool.
		 */
		SizeType getNbAvailableObjects() const {
			return this->objects.size();
		}
		
		/**
		 * Sets the number of objects available in the pool.
		 * @param newNbAvailableObjects New number of objects available in the
		 * pool.
		 */
		void setNbAvailableObjects(SizeType newNbAvailableObjects) {
			if (newNbAvailableObjects > this->objects.size()) {
				SizeType oldSize = this->objects.size();
				this->objects.resize(newNbAvailableObjects);
				
				for (SizeType i = oldSize; i < newNbAvailableObjects; ++i) {
					this->objects[i] = new T();
				}
			} else if (newNbAvailableObjects < this->objects.size()) {
				for (SizeType i = newNbAvailableObjects; i < this->objects.size(); ++i) {
					delete this->objects[i];
					this->objects[i] = NULL;
				}
				
				this->objects.resize(newNbAvailableObjects);
			}
		}
	private:
		/// Contains all the available objects.
		ObjectContainer objects;
	};
}

#endif
