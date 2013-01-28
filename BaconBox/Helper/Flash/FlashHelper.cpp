
#include "FlashHelper.h"
using namespace BaconBox;

AS3::local::var FlashHelper::callMethod(const AS3::local::var & var, const std::string & functionName, int argCount, AS3::local::var *args){
	AS3::local::var functionNameAS = AS3::local::internal::new_String(functionName.c_str());
	AS3::local::var functionAS = AS3::local::internal::getproperty(var, functionNameAS);
	return AS3::local::internal::call(functionAS, AS3::local::internal::_null, argCount, args);
}

AS3::local::var FlashHelper::getProperty(const AS3::local::var & var, const std::string & propertyName){
	AS3::local::var propertyNameAS = AS3::local::internal::new_String(propertyName.c_str());
	return  AS3::local::internal::getproperty(var, propertyNameAS);
}

void FlashHelper::setProperty(const AS3::local::var & var, const std::string & propertyName, AS3::local::var arg){
	AS3::local::var propertyNameAS = AS3::local::internal::new_String(propertyName.c_str());
	AS3::local::internal::setproperty(var, propertyNameAS, arg);
}


AS3::local::var FlashHelper::callFunction(const std::string & functionName, const std::string & ns, int argCount, AS3::local::var *args){
	AS3::local::var functionNameAS3 = AS3::local::internal::new_String(functionName.c_str());
	AS3::local::var nsAS3 = AS3::local::internal::new_Namespace(ns.c_str());
	AS3::local::var functionAS3 = AS3::local::internal::getlex(nsAS3, functionNameAS3);
	return AS3::local::internal::call(functionAS3, AS3::local::internal::_null, argCount, args);
}

AS3::local::var FlashHelper::construct(const std::string & className){
	AS3::local::var args[1] = {AS3::local::internal::new_String(className.c_str())};
	AS3::local::var ClassAS3 = FlashHelper::callFunction("getDefinitionByName", "flash.utils", 1, args);
	return AS3::local::internal::construct(ClassAS3);
}