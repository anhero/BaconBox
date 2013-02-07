
#include "FlashHelper.h"
#include "BaconBox/Console.h"
#include "BaconBox/PlatformFlagger.h"

using namespace BaconBox;

AS3::local::var FlashHelper::callMethod(const AS3::local::var & var, const std::string & functionName, int argCount, AS3::local::var *args){

	#ifdef BB_DEBUG
		try{
	#endif
	AS3::local::var functionNameAS = AS3::local::internal::new_String(functionName.c_str());
	AS3::local::var functionAS = AS3::local::internal::getproperty(var, functionNameAS);
	return AS3::local::internal::call(functionAS, AS3::local::internal::_null, argCount, args);
	#ifdef BB_DEBUG
		}
		catch(...){
		Console__error("Error calling method " << functionName << " on an AS3 object in FlashHelper. (See trace)");
		AS3_Trace("Method was called on:");
		AS3::local::internal::trace(var);
		throw;
		}
	#endif
}

AS3::local::var FlashHelper::getProperty(const AS3::local::var & var, const std::string & propertyName){
	#ifdef BB_DEBUG
		try{
	#endif
	AS3::local::var propertyNameAS = AS3::local::internal::new_String(propertyName.c_str());
	return  AS3::local::internal::getproperty(var, propertyNameAS);
		#ifdef BB_DEBUG
		}
		catch(...){
		Console__error("Error calling getProperty " << propertyName << " on an AS3 object in FlashHelper. (See trace)");
		AS3_Trace("GetProperty was called on:");
		AS3::local::internal::trace(var);
		throw;
		}
	#endif
}

void FlashHelper::setProperty(const AS3::local::var & var, const std::string & propertyName, AS3::local::var arg){
	#ifdef BB_DEBUG
		try{
	#endif
	AS3::local::var propertyNameAS = AS3::local::internal::new_String(propertyName.c_str());
	AS3::local::internal::setproperty(var, propertyNameAS, arg);
		#ifdef BB_DEBUG
		}
		catch(...){
		Console__error("Error calling setProperty " << propertyName << " on an AS3 object in FlashHelper. (See trace)");
		AS3_Trace("SetProperty was called on:");
		AS3::local::internal::trace(var);
		throw;
		}
	#endif
}


AS3::local::var FlashHelper::callFunction(const std::string & functionName, const std::string & ns, int argCount, AS3::local::var *args){
	#ifdef BB_DEBUG
		try{
	#endif
	AS3::local::var functionNameAS3 = AS3::local::internal::new_String(functionName.c_str());
	AS3::local::var nsAS3 = AS3::local::internal::new_Namespace(ns.c_str());
	AS3::local::var functionAS3 = AS3::local::internal::getlex(nsAS3, functionNameAS3);
	return AS3::local::internal::call(functionAS3, AS3::local::internal::_null, argCount, args);
	#ifdef BB_DEBUG
		}
		catch(...){
		Console__error("Error calling callFunction " << functionName << " in FlashHelper.");
		throw;
		}
	#endif
}

AS3::local::var FlashHelper::construct(const std::string & className){
	#ifdef BB_DEBUG
		try{
	#endif
	AS3::local::var args[1] = {AS3::local::internal::new_String(className.c_str())};
	AS3::local::var ClassAS3 = FlashHelper::callFunction("getDefinitionByName", "flash.utils", 1, args);
	return AS3::local::internal::construct(ClassAS3);
	#ifdef BB_DEBUG
		}
		catch(...){
		Console__error("Error constructing an as3 object " << className << " in FlashHelper.");
		throw;
		}
	#endif
}