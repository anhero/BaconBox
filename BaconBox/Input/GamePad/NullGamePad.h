/**
 * @file
 * @ingroup Input
 */
#ifndef BB_NULL_GAME_PAD_H
#define BB_NULL_GAME_PAD_H

namespace BaconBox {
	/**
	 * Null game pad device. Used when the platform doesn't have a game pad.
	 * @ingroup Input
	 */
	class NullGamePad {
	public:
		/**
		* Default constructor.
		*/
		NullGamePad();

		/**
		* Destructor.
		*/
		virtual ~NullGamePad();

		/**
		 * Updates the null game pad device.
		 */
		void updateDevice();
	};

}

#endif // BB_NULL_GAME_PAD_H
