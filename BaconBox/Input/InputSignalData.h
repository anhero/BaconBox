/**
 * @file
 * @ingroup Input
 */
#ifndef BB_INPUT_SIGNAL_DATA_H
#define BB_INPUT_SIGNAL_DATA_H

#include "BaconBox/SignalSlots/SignalData.h"

namespace BaconBox {
	/**
	 * Contains data for signals sent by input devices.
	 * @ingroup Input
	 */
	class InputSignalData : public SignalData {
	public:
		/**
		 * Default constructor.
		 */
		InputSignalData();
		/**
		 * Destructor.
		 */
		virtual ~InputSignalData();
	};
}

#endif
