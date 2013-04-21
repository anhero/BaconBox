#ifndef BB_IOS_TIME_HELPER_H
#define BB_IOS_TIME_HELPER_H

#include "BaconBox/PlatformFlagger.h"

#ifdef BB_IPHONE_PLATFORM

#include "BaconBox/Helper/TimeHelper.h"

namespace BaconBox {
	class IOSTimeHelper : public TimeHelper {
		friend class TimeHelper;
	public:
		void sleep(double duration);
	private:
		/// Time at which TimeHelper was initialized.
		double startTime;
		/// Last time the TimeHelper was refreshed.
		double lastTime;
		/**
		 * Default constructor.
		 */
		IOSTimeHelper();
		/**
		 * Destructor.
		 */
		~IOSTimeHelper();
		/**
		 * Refreshes the time variable.
		 */
		void refreshTime();
	};
}

#endif

#endif
