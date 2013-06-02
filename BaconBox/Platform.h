#ifndef BB_PLATFORM_H
#define BB_PLATFORM_H

namespace BaconBox {
    class Platform{
	public:

		
		bool isRetina;
		bool isIOS;
		bool isIphone;
		bool isIphone5;
		bool isIpad;
		bool isFlash;
		static Platform & getInstance();
		private:
		


		Platform();
		
	};
}

#endif


