/**
 * @file
 * @ingroup WindowDisplay
 */
#ifndef BB_FLASH_MAIN_WINDOW_H
#define BB_FLASH_MAIN_WINDOW_H

#include <AS3/AS3.h>
#include <AS3/AS3++.h>

#include "BaconBox/Display/Window/MainWindow.h"

namespace BaconBox {

	
	class FlashMainWindow : public MainWindow {
		friend class Engine;
	public:


		void onBaconBoxInit(unsigned int resolutionWidth,
		                  unsigned int resolutionHeight,
		                  float contextWidth,
		                  float contextHeight);

	
		void show();


		void setCaption(const std::string &caption);


		bool isFullScreen() const;


		void setFullScreen(bool newFullScreen);


		bool isInputGrabbed() const;


		void setInputGrabbed(bool newInputGrabbed);


		void setResolution(unsigned int resolutionWidth, unsigned int resolutionHeight);
        

        void hideCursor();
        

        void showCursor();


		void setContextSize(float newContextWidth,
		                    float newContextHeight);
	private:

		AS3::local::var stage;

		FlashMainWindow();

	
		~FlashMainWindow();

	};
}

#endif
