#include "Batch.h"

namespace BaconBox {
	Batch::Batch() : Component() {
	}
	
	Batch::Batch(const Batch &src) : Component(src) {
	}
	
	Batch::~Batch() {
	}
	
	Batch &Batch::operator=(const Batch &src) {
		if (this != &src) {
		}
		
		return *this;
	}
	
	Batch *Batch::clone() const {
		return new Batch(*this);
	}
	
	void Batch::receiveMessage(int senderID, int destID, int message, void *data) {
	}
}
