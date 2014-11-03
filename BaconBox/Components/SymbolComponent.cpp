#include "Transform.h"

#include "BaconBox/Core/Entity.h"
#include "BaconBox/Console.h"
#include "BaconBox/Debug.h"

#include "BaconBox/Helper/MathHelper.h"
#include "BaconBox/Components/MatrixComponent.h"
#include "BaconBox/Components/DefaultMatrix.h"
#include "SymbolComponent.h"
#include "BaconBox/MovieClipEntity/MovieClipEntity.h"
#include "DefaultMatrix.h"
namespace BaconBox {
	 BB_ID_IMPL(SymbolComponent);
	
    const std::string SymbolComponent::NO_KEY = std::string("");
	SymbolComponent::SymbolComponent() : Component(), symbol(NULL){
	}

	
	Symbol * SymbolComponent::getSymbol(){
	    return symbol;
	}

	const std::string & SymbolComponent::getKey(){
        if(symbol){
         return symbol->key;
        }
        else{
            return SymbolComponent::NO_KEY;
        }
        
	}


	
	void SymbolComponent::setSymbol(Symbol * symbol){
	#ifdef BB_DEBUG
		if(Debug::getInstance().trackMovieClip){
			if(this->symbol != NULL)Debug::getInstance().destroyMovieClip(this->symbol->key);
			Debug::getInstance().createMovieClip(symbol->key);
		}
	#endif
	    this->symbol = symbol;
	}

	
	SymbolComponentProxy::SymbolComponentProxy(Entity* entity, bool mustAddComponent): BB_PROXY_CONSTRUCTOR(new SymbolComponent())  {
	}
	    
	const std::string & SymbolComponentProxy::getKey(){
	    return reinterpret_cast<SymbolComponent*>(component)->getKey();
	}
	    
	Symbol * SymbolComponentProxy::getSymbol(){
	    return reinterpret_cast<SymbolComponent*>(component)->getSymbol();
	}

	void SymbolComponentProxy::setSymbol(Symbol * symbol){
	    reinterpret_cast<SymbolComponent*>(component)->setSymbol(symbol);
	}

	
	
}