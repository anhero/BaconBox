#include "Transform.h"

#include "BaconBox/Core/Entity.h"
#include "BaconBox/Console.h"
#include "BaconBox/Helper/MathHelper.h"
#include "BaconBox/Components/MatrixComponent.h"
#include "BaconBox/Components/DefaultMatrix.h"
#include "SymbolComponent.h"
#include "BaconBox/MovieClipEntity/MovieClipEntity.h"
#include "DefaultMatrix.h"
namespace BaconBox {
	 BB_ID_IMPL(SymbolComponent);
	
	SymbolComponent::SymbolComponent() : Component(), symbol(NULL){
	}

	
	Symbol * SymbolComponent::getSymbol(){
	    return symbol;
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