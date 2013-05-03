/**
 * @file
 * @ingroup Input
 */
#ifndef BB_FLASHKEYBOARD_H
#define BB_FLASHKEYBOARD_H
#include "BaconBox/Input/Keyboard/Key.h"
#include "BaconBox/Input/Keyboard/Keyboard.h"
#include <AS3/AS3.h>
#include <AS3/AS3++.h>

namespace BaconBox {

	class FlashKeyboard : public Keyboard {
		friend class InputManager;
	protected:
		/**
		 * Default constructor.
		 */
		FlashKeyboard();
		
		/**
		 * Destructor.
		 */
		~FlashKeyboard();
	
		void updateDevice();

	private:

		AS3::local::var keyboardFun;
		static AS3::local::var keyboardEventListener(void *arg, AS3::local::var as3Args);
		
		std::map<unsigned int, Key::Enum> mappings;

		std::set<Key::Enum> keysPressed;

		AS3::local::var keyDownEvent;
		AS3::local::var keyUpEvent;

		
		void fillMappings();

	};
}

#endif
