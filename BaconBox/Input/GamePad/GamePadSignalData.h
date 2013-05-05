/**
 * @file
 * @ingroup Input
 */
#ifndef BB_GAME_PAD_SIGNAL_DATA_H
#define BB_GAME_PAD_SIGNAL_DATA_H

#include "BaconBox/Input/InputSignalData.h"
#include "BaconBox/Input/GamePad/GamePadState.h"

namespace BaconBox {
	/**
	 * Base class that contains data needed by slots that listen to signals
	 * sent by a gamepad.
	 * @ingroup Input
	 */
	class GamePadSignalData : public InputSignalData {
	public:
		/**
		 * Parameterized constructor.
		 * @param newGamePadState State of the game pad that sent the signal.
		 * @param gamePadIndex Index of the game pad.
		 */
		GamePadSignalData(const GamePadState &newGamePadState,
		                  size_t gamePadIndex);

		/**
		 * Destructor.
		 */
		virtual ~GamePadSignalData();

		/// Reference to the state of the game pad that sent the signal.
		const GamePadState &gamePadState;


		const size_t gamePadIndex;
	};
}

#endif
