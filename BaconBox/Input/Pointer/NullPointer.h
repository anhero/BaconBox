/**
 * @file
 * @ingroup Input
 */
#ifndef BB_NULL_POINTER_H
#define BB_NULL_POINTER_H

#include "BaconBox/Input/Pointer/Pointer.h"

namespace BaconBox {
	/**
	 * Null pointing device, used when the platform doesn't have a pointing
	 * device.
	 * @ingroup Input
	 */
	class NullPointer : public Pointer {
	public:
		/**
		 * Default constructor.
		 */
		NullPointer();

		/**
		 * Destructor.
		 */
		~NullPointer();

		/**
		 * Updates the pointing device. It actually does not do anything.
		 */
		void updateDevice();
	};
}

#endif // BB_NULL_POINTER_H
