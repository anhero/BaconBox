
#ifndef BB_FLASHHELPER_H
#define BB_FLASHHELPER_H


#include "BaconBox/PlatformFlagger.h"
#ifdef BB_FLASH_PLATFORM	
	#include <AS3/AS3.h>
	#include <AS3/AS3++.h>
#endif	
#include "BaconBox/MovieClipEntity/MovieClipEntity.h"

namespace BaconBox {
	
	class FlashHelper {
	public:
		static AS3::local::var callMethod(const AS3::local::var & var, const std::string & functionName, int argCount, AS3::local::var *args);
		static AS3::local::var getProperty(const AS3::local::var & var, const std::string & propertyName);
		static void setProperty(const AS3::local::var & var, const std::string & propertyName, AS3::local::var arg);
		static MovieClipEntity * getMCEntityFromMC(AS3::local::var mc);
		static AS3::local::var getMCFromMCEntity(MovieClipEntity *entity);

		static AS3::local::var callFunction(const std::string & functionName, const std::string & ns, int argCount, AS3::local::var *args);


		static AS3::local::var construct(const std::string & className);
	private:
		static AS3::local::var getDefinitionByName(const std::string & className);
		static AS3::local::var MOVIECLIP_CLASS;
            
	};
	
}

#endif
