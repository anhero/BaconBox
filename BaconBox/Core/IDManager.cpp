#include "IDManager.h"

namespace BaconBox {
	IDManager &IDManager::getInstance() {
		static IDManager instance;
		return instance;
	}
	
	int IDManager::getID() {
		return getInstance().counter++;
	}
	
	IDManager::IDManager() : counter(0) {
	}
}
