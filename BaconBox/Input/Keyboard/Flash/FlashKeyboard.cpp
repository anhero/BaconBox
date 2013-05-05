#include "BaconBox/Input/Keyboard/Flash/FlashKeyboard.h"
#include "BaconBox/Core/Flash/FlashEngine.h"
#include "BaconBox/Console.h"
#include "BaconBox/Helper/Flash/FlashHelper.h"

using namespace BaconBox;

FlashKeyboard::FlashKeyboard() : Keyboard(), mappings(), keysPressed() {
	 inline_as3("import flash.events.KeyboardEvent; \n");

	 AS3_GetVarxxFromVar(keyDownEvent, KeyboardEvent.KEY_DOWN);
	AS3_GetVarxxFromVar(keyUpEvent, KeyboardEvent.KEY_UP);

	AS3::local::var stage = FlashEngine::getStage();
	AS3::local::var eventType;
	AS3::local::var args[2];

	keyboardFun = args[1] = AS3::local::internal::new_Function(keyboardEventListener, reinterpret_cast<void*>(this));


	args[0]= keyDownEvent;
	FlashHelper::callMethod(stage, "addEventListener", 2, args);

	args[0] = keyUpEvent;
	FlashHelper::callMethod(stage, "addEventListener", 2, args);
	fillMappings();
}




FlashKeyboard::~FlashKeyboard() {
	inline_as3("import flash.events.KeyboardEvent; \n");

	AS3::local::var stage = FlashEngine::getStage();
	AS3::local::var eventType;
	AS3::local::var args[2];

	args[1] = keyboardFun;

	AS3_GetVarxxFromVar(args[0], KeyboardEvent.KEY_DOWN);
	FlashHelper::callMethod(stage, "removeEventListener", 2, args);

	AS3_GetVarxxFromVar(args[0], KeyboardEvent.KEY_UP);
	FlashHelper::callMethod(stage, "removeEventListener", 2, args);
}


 AS3::local::var FlashKeyboard::keyboardEventListener(void *arg, AS3::local::var as3Args){
 	FlashKeyboard* self = reinterpret_cast<FlashKeyboard*>(arg);
	AS3::local::var event = FlashHelper::callMethod(as3Args, "pop", 0, NULL);
	AS3::local::var eventType = FlashHelper::getProperty(event, "type");
	AS3::local::var keyCodeAS3 = FlashHelper::getProperty(event, "keyCode");
	unsigned int keyCode = AS3::local::internal::uns_valueOf(keyCodeAS3);
	Key::Enum pressedKey = Key::INVALID;
	std::map<unsigned int, Key::Enum>::iterator i = self->mappings.find(keyCode);
	if(i != self->mappings.end()){
		pressedKey = i->second;
		if(AS3::local::internal::equals(eventType, self->keyDownEvent)){
			self->keysPressed.insert(pressedKey);
		}
		else if(AS3::local::internal::equals(eventType, self->keyUpEvent)){
			self->keysPressed.erase(pressedKey);
		}
	}

	

	return AS3::local::internal::_null;
}

void FlashKeyboard::fillMappings() {
	inline_as3("import flash.ui.Keyboard; \n");

	AS3::local::var keycodeAS;

	AS3_GetVarxxFromVar(keycodeAS, Keyboard.A);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::A;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.B);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::B;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.C);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::C;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.D);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::D;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.E);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::E;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.F);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::F;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.G);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::G;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.H);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::H;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.I);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::I;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.J);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::J;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.K);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::K;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.L);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::L;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.M);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::M;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.N);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::N;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.O);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::O;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.P);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::P;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.Q);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::Q;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.R);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::R;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.S);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::S;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.T);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::T;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.U);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::U;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.V);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::V;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.W);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::W;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.X);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::X;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.Y);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::Y;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.Z);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::Z;

	AS3_GetVarxxFromVar(keycodeAS, Keyboard.NUMBER_1);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::D1;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.NUMBER_2);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::D2;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.NUMBER_3);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::D3;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.NUMBER_4);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::D4;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.NUMBER_5);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::D5;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.NUMBER_6);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::D6;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.NUMBER_7);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::D7;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.NUMBER_8);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::D8;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.NUMBER_9);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::D9;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.NUMBER_0);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::D0;


	AS3_GetVarxxFromVar(keycodeAS, Keyboard.CONTROL);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::LEFT_CONTROL;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.ALTERNATE);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::LEFT_ALT;

	AS3_GetVarxxFromVar(keycodeAS, Keyboard.SHIFT);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::LEFT_SHIFT;

	AS3_GetVarxxFromVar(keycodeAS, Keyboard.ENTER);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::ENTER;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.ESCAPE);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::ESCAPE;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.BACKSPACE);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::BACKSPACE;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.TAB);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::TAB;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.SPACE);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::SPACE;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.MINUS);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::MINUS;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.EQUAL);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::EQUAL;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.LEFTBRACKET);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::OPEN_BRACKETS;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.RIGHTBRACKET);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::CLOSE_BRACKETS;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.BACKSLASH);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::BACKSLASH;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.QUOTE);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::NUMBER_SIGN;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.SEMICOLON);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::SEMICOLON;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.COMMA);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::COMMA;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.PERIOD);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::PERIOD;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.SLASH);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::SLASH;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.CAPS_LOCK);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::CAPS_LOCK;


	AS3_GetVarxxFromVar(keycodeAS, Keyboard.F1);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::F1;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.F2);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::F2;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.F3);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::F3;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.F4);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::F4;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.F5);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::F5;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.F6);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::F6;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.F7);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::F7;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.F8);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::F8;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.F9);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::F9;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.F10);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::F10;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.F11);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::F11;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.F12);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::F12;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.F13);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::F13;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.F14);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::F14;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.F15);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::F15;



	AS3_GetVarxxFromVar(keycodeAS, Keyboard.HOME);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::HOME;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.PAGE_UP);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::PAGE_UP;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.DELETE);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::DELETEKEY;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.END);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::END;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.PAGE_DOWN);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::PAGE_DOWN;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.INSERT);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::INSERT;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.RIGHT);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::RIGHT;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.LEFT);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::LEFT;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.DOWN);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::DOWN;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.UP);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::UP;


	AS3_GetVarxxFromVar(keycodeAS, Keyboard.NUMPAD_MULTIPLY);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::MULTIPLY;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.MINUS);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::MINUS;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.NUMPAD_ADD);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::PLUS;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.NUMPAD_ENTER);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::NUM_PAD_ENTER;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.NUMPAD_1);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::NUM_PAD_1;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.NUMPAD_2);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::NUM_PAD_2;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.NUMPAD_3);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::NUM_PAD_3;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.NUMPAD_4);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::NUM_PAD_4;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.NUMPAD_5);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::NUM_PAD_5;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.NUMPAD_6);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::NUM_PAD_6;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.NUMPAD_7);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::NUM_PAD_7;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.NUMPAD_8);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::NUM_PAD_8;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.NUMPAD_9);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::NUM_PAD_9;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.NUMPAD_0);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::NUM_PAD_0;
	AS3_GetVarxxFromVar(keycodeAS, Keyboard.NUMPAD_DECIMAL);
	mappings[AS3::local::internal::uns_valueOf(keycodeAS)] = Key::NUM_PAD_PERIOD;
}


void FlashKeyboard::updateDevice() {
		getPreviousKeys() = getKeys();
		for(std::vector<bool>::iterator i = getKeys().begin(); i != getKeys().end(); i++){
			(*i) = false;
		}

		for(std::set<Key::Enum>::iterator i = keysPressed.begin(); i != keysPressed.end(); i++){
			getKeys()[*i] = true;
		}

		for(Key::Enum i = 0; i < Key::NB_KEYS;++i) {
		if(isKeyPressed(i)) {
			keyPress(KeySignalData(state, i));
		} else if(isKeyHeld(i)) {
			keyHold(KeySignalData(state, i));
		} else if(isKeyReleased(i)) {
			keyRelease(KeySignalData(state, i));
		}
	}

}
