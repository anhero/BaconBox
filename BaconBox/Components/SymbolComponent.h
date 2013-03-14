#ifndef BB_TRANSFORM_H
#define BB_TRANSFORM_H

#include "BaconBox/Symbol.h"
namespace BaconBox {
	class MatrixComponent;
	/**
	 * Component that manages the entity's position, orientation and scaling
	 * values.
	 */
	class SymbolComponent : public Component {
	public:
		BB_ID_HEADER;
		
		SymbolComponent();
		
		Symbol * getSymbol();
		void setSymbol(Symbol * symbol);

	private:
	    
	    Symbol * symbol;
		
	};


	class SymbolComponentProxy : public ComponentProxy {
	public:
		SymbolComponentProxy(Entity *entity, bool mustAddComponent = true);
		
		Symbol * getSymbol();
		void setSymbol(Symbol * symbol);


	private:

	};
}

#endif
