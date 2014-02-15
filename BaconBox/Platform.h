#ifndef BB_PLATFORM_H
#define BB_PLATFORM_H

namespace BaconBox {
    class Platform{
	public:

		
		bool isRetina;
		bool isMobile;
		bool isIOS;
		bool isIphone;
		bool isIOSWide;
		bool isIpad;
		bool  isIpod;
		bool isFlash;
		
		static Platform & getInstance();
		private:
		


		Platform();
		
	};
}

#endif


