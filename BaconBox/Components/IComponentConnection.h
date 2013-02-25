#ifndef BB_ICOMPONENT_DEFINITION_H
#define BB_ICOMPONENT_DEFINITION_H

namespace BaconBox {
	class Component;
	class ComponentAddedData;
	
	class IComponentConnection {
	public:
		virtual void componentRemoved(int id) = 0;
		virtual void componentAdded(const ComponentAddedData &data) = 0;
	};
}

#endif
