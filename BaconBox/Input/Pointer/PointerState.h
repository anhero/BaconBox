/**
 * @file
 * @ingroup Input
 */
#ifndef BB_POINTER_STATE_H
#define BB_POINTER_STATE_H

#include <vector>

#include "BaconBox/Input/InputState.h"
#include "BaconBox/Input/Pointer/CursorState.h"

namespace BaconBox {
	/**
	 * Represents the current state of a pointing device.
	 * @ingroup Input
	 */
	class PointerState : public InputState {
		friend class Pointer;
	public:
		/// Default number of cursors a pointer's state has.
		static const size_t DEFAULT_NB_CURSORS;

		/**
		 * Parameterizable default constructor.
		 * @param nbCursors Number of cursors the pointing device(s) can
		 * support.
		 */
		PointerState(size_t nbCursors = DEFAULT_NB_CURSORS);

		/**
		 * Destructor.
		 */
		~PointerState();

		/**
		 * Gets the state of a cursor.
		 * @param index Index of the cursor's state to get.
		 */
		const CursorState& getCursorState(size_t index = 0) const;
	private:
		/// Cursors' states.
		std::vector<CursorState> cursors;

		/**
		 * Gets a cursor's position.
		 * @param index Index of the cursor to get.
		 * @return Reference to the cursor's position.
		 */
		const Vector2& getCursorPosition(size_t index);
		void setCursorPosition(unsigned int index, Vector2 pos);
		/**
		 * Gets a cursor's previous position.
		 * @param index Index of the cursor to get.
		 * @return Reference to the cursor's previous position.
		 */
		Vector2& getCursorPreviousPosition(size_t index);

		/**
		 * Gets a cursor's buttons.
		 * @param index Index of the cursor to get.
		 * @return Reference to the cursor's buttons.
		 */
		std::vector<bool>& getCursorButtons(size_t index);

		/**
		 * Gets a cursor's previous buttons.
		 * @param index Index of the cursor to get.
		 * @return Reference to the cursor's previous buttons.
		 */
		std::vector<bool>& getCursorPreviousButtons(size_t index);
	};
}

#endif
