#include "BaconBox/Input/InputManager.h"

#include "BaconBox/PlatformFlagger.h"

#ifdef BB_ACCELEROMETER_INCLUDE
#include BB_ACCELEROMETER_INCLUDE
#endif

#ifdef BB_GAME_PAD_INCLUDE
#include BB_GAME_PAD_INCLUDE
#endif

#ifdef BB_KEYBOARD_INCLUDE
#include BB_KEYBOARD_INCLUDE
#endif

#ifdef BB_POINTER_INCLUDE
#include BB_POINTER_INCLUDE
#endif

#ifdef BB_INPUT_MANAGER_INCLUDE
#include BB_INPUT_MANAGER_INCLUDE
#endif

using namespace BaconBox;

	BB_SINGLETON_IMPL(BaseInputManager)


InputManager &InputManager::getInstance() {
	return * static_cast<InputManager *>(BB_INPUT_MANAGER_IMPL);
}		


Accelerometer* InputManager::getDefaultAccelerometer() {
	return InputManager::getInstance().getAccelerometer();
}

GamePad* InputManager::getDefaultGamePad() {
	return InputManager::getInstance().getGamePad();
}

Keyboard* InputManager::getDefaultKeyboard() {
	return InputManager::getInstance().getKeyboard();
}

Pointer* InputManager::getDefaultPointer() {
	return InputManager::getInstance().getPointer();
}

size_t InputManager::getNbAccelerometers() const {
	return accelerometers.size();
}

size_t InputManager::getNbGamePads() const {
	return gamePads.size();
}

size_t InputManager::getNbKeyboards() const {
	return keyboards.size();
}

size_t InputManager::getNbPointers() const {
	return pointers.size();
}

void InputManager::setNbAccelerometers(size_t nb) {
	if (nb > accelerometers.size()) {
		size_t oldSize = accelerometers.size();
		accelerometers.resize(nb, NULL);
		for(size_t i = oldSize; i < nb; ++i) {
			accelerometers[i] = BB_ACCELEROMETER_IMPL;
		}
	} else if(nb < accelerometers.size()) {
		for(size_t i = nb; i < accelerometers.size(); ++i) {
			if(accelerometers[i]) {
				delete accelerometers[i];
			}
		}
		accelerometers.resize(nb);
	}
}

void InputManager::setNbGamePads(size_t nb) {
	if (nb > gamePads.size()) {
		std::vector<GamePad*>::size_type oldSize = gamePads.size();
		gamePads.resize(nb, NULL);
		for(std::vector<GamePad*>::size_type i = oldSize; i < nb; ++i) {
			gamePads[i] = BB_GAME_PAD_IMPL;
		}
	} else if(nb < gamePads.size()) {
		for(size_t i = nb; i < gamePads.size(); ++i) {
			if(gamePads[i]) {
				delete gamePads[i];
			}
		}
		gamePads.resize(nb);
	}
}

void InputManager::setNbKeyboards(size_t nb) {
	if (nb > keyboards.size()) {
		size_t oldSize = keyboards.size();
		keyboards.resize(nb, NULL);
		for(size_t i = oldSize; i < nb; ++i) {
			keyboards[i] = BB_KEYBOARD_IMPL;
		}
	} else if(nb < keyboards.size()) {
		for(size_t i = nb; i < keyboards.size(); ++i) {
			if(keyboards[i]) {
				delete keyboards[i];
			}
		}
		keyboards.resize(nb);
	}
}

void InputManager::setNbPointers(size_t nb) {
	if (nb > pointers.size()) {
		size_t oldSize = pointers.size();
		pointers.resize(nb, NULL);
		for(size_t i = oldSize; i < nb; ++i) {
			pointers[i] = BB_POINTER_IMPL;
		}
	} else if(nb < pointers.size()) {
		for(size_t i = nb; i < pointers.size(); ++i) {
			if(pointers[i]) {
				delete pointers[i];
			}
		}
		pointers.resize(nb);
	}
}

Accelerometer* InputManager::getAccelerometer(size_t index) {
	if(index >= accelerometers.size()) {
		return NULL;
	} else {
		return accelerometers[index];
	}
}

GamePad* InputManager::getGamePad(size_t index) {
	if(index >= gamePads.size()) {
		return NULL;
	} else {
		return gamePads[index];
	}
}

Keyboard* InputManager::getKeyboard(size_t index) {
	if(index >= keyboards.size()) {
		return NULL;
	} else {
		return keyboards[index];
	}
}

Pointer* InputManager::getPointer(size_t index) {
	if(index >= pointers.size()) {
		return NULL;
	} else {
		return pointers[index];
	}
}

void InputManager::dontDeleteAccelerometers() {
	deleteAccelerometers = false;
}
void InputManager::dontDeleteGamePads() {
	deleteGamePads = false;
}
void InputManager::dontDeleteKeyboards() {
	deleteKeyboards = false;
}
void InputManager::dontDeletePointers() {
	deletePointers = false;
}

void InputManager::deleteAccelerometersOnQuit() {
	deleteAccelerometers = true;
}
void InputManager::deleteGamePadsOnQuit() {
	deleteGamePads = true;
}

void InputManager::deleteKeyboardsOnQuit() {
	deleteKeyboards = true;
}

void InputManager::deletePointersOnQuit() {
	deletePointers = true;
}

InputManager::InputManager() : deleteAccelerometers(true), deleteGamePads(true),
deleteKeyboards(true), deletePointers(this) {
}

InputManager::~InputManager() {
	// We delete all the devices.
	if(deleteAccelerometers) {
		for (std::vector<Accelerometer*>::iterator i = accelerometers.begin();
			 i != accelerometers.end(); ++i) {
			if(*i) {
				delete *i;
			}
		}
	}

	if(deleteGamePads) {
		for (std::vector<GamePad*>::iterator i = gamePads.begin();
			 i != gamePads.end(); ++i) {
			if(*i) {
				delete *i;
			}
		}
	}

	if(deleteKeyboards) {
		for (std::vector<Keyboard*>::iterator i = keyboards.begin();
			 i != keyboards.end(); ++i) {
			if(*i) {
				delete *i;
			}
		}
	}

	if(deletePointers) {
		for (std::vector<Pointer*>::iterator i = pointers.begin();
			 i != pointers.end(); ++i) {
			if(*i) {
				delete *i;
			}
		}
	}
}

void InputManager::update() {
	for (std::vector<Accelerometer*>::iterator i = accelerometers.begin();
		 i != accelerometers.end(); ++i) {
		if(*i) {
			(*i)->updateDevice();
		}
	}
	for (std::vector<GamePad*>::iterator i = gamePads.begin();
		 i != gamePads.end(); ++i) {
		if(*i) {
			(*i)->updateDevice();
		}
	}
	for (std::vector<Keyboard*>::iterator i = keyboards.begin();
		 i != keyboards.end(); ++i) {
		if(*i) {
			(*i)->updateDevice();
		}
	}
	for (std::vector<Pointer*>::iterator i = pointers.begin();
		 i != pointers.end(); ++i) {
		if(*i) {
			(*i)->updateDevice();
		}
	}
}
