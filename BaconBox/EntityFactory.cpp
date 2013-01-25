#include "EntityFactory.h"

#include "BaconBox/PlatformFlagger.h"
#ifdef BB_FLASH_PLATEFORM	
	#include <AS3/AS3.h>
	#include <AS3/AS3++.h>
#endif	
namespace BaconBox {
	EntityFactory::EntityFactory(){
	    
	}
	
	Entity * EntityFactory::getEntity(const std::string & key){
	#ifdef BB_FLASH_PLATEFORM	
	AS3::local::var className = AS3::local::internal::new_String(key.c_str());
	AS3::local::var cc = AS3::local::internal::getlex(className);
	AS3::local::var mc = AS3::local::internal::construct(cc);
	
	
	AS3::local::var propertyNameAS = AS3::local::internal::new_String("entity");
	AS3::local::var entityPointerAS3 = AS3::local::internal::getproperty(mc, propertyNameAS);
	Entity * entityPointer = (Entity*)int_valueOf(entityPointerAS3);
	return entityPointer;
	#endif	  
	}
}

