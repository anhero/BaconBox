#ifndef BB_SYMBOLCOMPONENT_H
#define BB_SYMBOLCOMPONENT_H

#include "BaconBox/Symbol.h"
#include "MatrixComponent.h"
#include "EntityContainer.h"
namespace BaconBox {
	class DefaultMatrix;
	/**
	 * Component that manages the entity's position, orientation and scaling
	 * values.
	 */
	class SymbolComponent : public Component {
	    friend class DefaultMatrix;
	public:
		BB_ID_HEADER;
		
		SymbolComponent();
		
		Symbol * getSymbol();
		void setSymbol(Symbol * symbol);
	private:
		void initializeConnections();
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
