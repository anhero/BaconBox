#include "BaconBox/Display/BatchManager.h"

#include <limits>

namespace BaconBox {
	const size_t BatchManager::INVALID_ID = std::numeric_limits<size_t>::max();
	
	BatchManager::BatchManager() {
	}
	
	BatchManager::BatchManager(const BatchManager &src) {
	}
	
	BatchManager::~BatchManager() {
	}
	
	BatchManager &BatchManager::operator=(const BatchManager &src) {
		if (this != &src) {
		}
		
		return *this;
	}
}
