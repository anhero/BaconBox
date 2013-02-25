#ifndef BB_ComponentAddedData_H
#define BB_ComponentAddedData_H

namespace BaconBox {
	class Component;
	
	struct ComponentAddedData {
	public:
		ComponentAddedData(int newId, Component *newComponent);
		
		ComponentAddedData(const ComponentAddedData &src);
		
		ComponentAddedData &operator=(const ComponentAddedData &src);
		
		int id;
		
		Component *component;
	};
}

#endif /* defined(BB_ComponentAddedData_H) */

