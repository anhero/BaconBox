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
		void setMatrixFromParentFrame();
	private:
		bool customMatrixSet;
		void initializeConnections();
		Symbol * symbol;
		DefaultMatrix * defaultMatrix;
		EntityContainer * entityContainer;
	};


	class SymbolComponentProxy : public ComponentProxy {
	public:
		SymbolComponentProxy(Entity *entity, bool mustAddComponent = true);
		void setMatrixFromParentFrame();
		Symbol * getSymbol();
		void setSymbol(Symbol * symbol);

	private:

	};
}

#endif
