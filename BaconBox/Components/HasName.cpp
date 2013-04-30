#include "HasName.h"
#include "BaconBox/Console.h"
namespace BaconBox {
	 BB_ID_IMPL(HasName);
	
	 
	 HasName::HasName(const std::string & name){
	     this->name = name;
	 }
	 
	const std::string &HasName::getName() const {
		return this->name;
	}

	void HasName::setName(const std::string &newName) {
		this->name = newName;
	}
	
	HasNameProxy::HasNameProxy(Entity* entity, const std::string & name, bool mustAddComponent):BB_PROXY_CONSTRUCTOR(new HasName(name)){
	    
	}
	
	const std::string &HasNameProxy::getName() const {
		return reinterpret_cast<HasName*>(component)->getName();;
	}
	
	void HasNameProxy::setHasName(HasName * hasName){
	    component = hasName;
	    entity->addComponent(hasName);
	}


	void HasNameProxy::setName(const std::string &newName) {
		reinterpret_cast<HasName*>(component)->setName(newName);
	}
	
}