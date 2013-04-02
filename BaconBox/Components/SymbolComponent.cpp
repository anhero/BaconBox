#include "Transform.h"

#include "BaconBox/Core/Entity.h"
#include "BaconBox/Console.h"
#include "BaconBox/Helper/MathHelper.h"
#include "BaconBox/Components/MatrixComponent.h"
#include "BaconBox/Components/DefaultMatrix.h"
#include "SymbolComponent.h"
#include "MovieClipEntity/MovieClipEntity.h"
#include "DefaultMatrix.h"
namespace BaconBox {
	 BB_ID_IMPL(SymbolComponent);
	
	SymbolComponent::SymbolComponent() : Component(), symbol(NULL), defaultMatrix(NULL), entityContainer(NULL){
		this->initializeConnections();
	}

	
	Symbol * SymbolComponent::getSymbol(){
	    return symbol;
	}


void SymbolComponent::initializeConnections() {
		// We add the connections.
		this->addConnection(new ComponentConnection<DefaultMatrix>(&this->defaultMatrix));
		this->addConnection(new ComponentConnection<EntityContainer>(&this->entityContainer));
		this->refreshConnections();
	}
	
	void SymbolComponent::setSymbol(Symbol * symbol){
	    this->symbol = symbol;
	}

	
	SymbolComponentProxy::SymbolComponentProxy(Entity* entity, bool mustAddComponent): BB_PROXY_CONSTRUCTOR(new SymbolComponent())  {
	}
	    

	    
	Symbol * SymbolComponentProxy::getSymbol(){
	    return reinterpret_cast<SymbolComponent*>(component)->getSymbol();
	}

	void SymbolComponentProxy::setSymbol(Symbol * symbol){
	    reinterpret_cast<SymbolComponent*>(component)->setSymbol(symbol);
	}

	
	
}