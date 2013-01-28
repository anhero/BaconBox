
#ifndef BB_FLASHHELPER_H
#define BB_FLASHHELPER_H


#include "BaconBox/PlatformFlagger.h"
#ifdef BB_FLASH_PLATEFORM	
	#include <AS3/AS3.h>
	#include <AS3/AS3++.h>
#endif	

namespace BaconBox {
	
	class FlashHelper {
	public:
		static AS3::local::var callMethod(const AS3::local::var & var, const std::string & functionName, int argCount, AS3::local::var *args);
		static AS3::local::var getProperty(const AS3::local::var & var, const std::string & propertyName);
		static void setProperty(const AS3::local::var & var, const std::string & propertyName, AS3::local::var arg);


		static AS3::local::var callFunction(const std::string & functionName, const std::string & ns, int argCount, AS3::local::var *args);


		static AS3::local::var construct(const std::string & className);
	private:
            
	};
	
}

#endif
