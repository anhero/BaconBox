#ifndef BB_PLATFORM_H
#define BB_PLATFORM_H

namespace BaconBox {
    class Platform{
	public:
		static bool isIphone();
		static bool isFlash();
		private:
		static Platform & getInstance();
		
		
		bool iphonePlatform;
		bool flashPlatform;
		Platform();
		
	};
}

#endif


