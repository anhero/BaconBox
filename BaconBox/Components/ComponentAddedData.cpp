#include "ComponentAddedData.h"

namespace BaconBox {
	ComponentAddedData::ComponentAddedData(int newId, Component *newComponent) : id(newId), component(newComponent) {
	}
	
	ComponentAddedData::ComponentAddedData(const ComponentAddedData &src) : id(src.id), component(src.component) {
	}
	
	ComponentAddedData &ComponentAddedData::operator=(const ComponentAddedData &src) {
		if (this != &src) {
			this->id = src.id;
			this->component = src.component;
		}
		
		return *this;
	}
}
