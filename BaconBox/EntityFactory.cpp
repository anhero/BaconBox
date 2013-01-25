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
			AS3::local::var functionName = AS3::local::internal::new_String("getDefinitionByName");
			AS3::local::var ns = AS3::local::internal::new_Namespace("flash.utils");

			AS3::local::var functionAS3 = AS3::local::internal::getlex(ns, functionName);
			AS3::local::var args[1] = {className};
			AS3::local::var mcClass = AS3::local::internal::call(functionAS3, AS3::local::internal::_null, 1, args);
			AS3::local::var mc =  AS3::local::internal::construct(mcClass);

			AS3::local::var propertyNameAS = AS3::local::internal::new_String("entity");
			AS3::local::var entity = AS3::local::internal::getproperty(mc, propertyNameAS);

			propertyNameAS = AS3::local::internal::new_String("swigCPtr");
			AS3::local::var entityPointerAS3 = AS3::local::internal::getproperty(entity, propertyNameAS);
			Entity * entityPointer = (Entity*)int_valueOf(entityPointerAS3);
			return entityPointer;
		#endif	  
	}
}

