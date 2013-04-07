/**
 * @file
 * @ingroup Input
 */
#ifndef BB_GAME_PAD_BUTTON_SIGNAL_DATA_H
#define BB_GAME_PAD_BUTTON_SIGNAL_DATA_H

#include "BaconBox/Input/GamePad/GamePadSignalData.h"

namespace BaconBox {
	/**
	 * Contains data needed by slots that listen to signals sent by the game pad
	 * when a button is pressed, held or released.
	 * @ingroup Input
	 */
	class GamePadButtonSignalData : public GamePadSignalData {
	public:
		/**
		 * Parameterized constructor.
		 * @param newGamePadState State of the game pad that sent the signal.
		 * @param newButtonIndex Index of the button concerned by the signal.
		 * @param gamePadIndex Index of the game pad.
		 */
		GamePadButtonSignalData(const GamePadState& newGamePadState,
								size_t newButtonIndex, size_t gamePadIndex);
		/**
		 * Destructor.
		 */
		~GamePadButtonSignalData();
		
		/// Index of the button concerned by the signal.
		const size_t buttonIndex;
	};
}

#endif
