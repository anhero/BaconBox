/**
 * @file
 * @ingroup WindowDisplay
 */
#ifndef BB_IOS_MAIN_WINDOW_H
#define BB_IOS_MAIN_WINDOW_H

#include "BaconBox/Display/Window/MainWindow.h"
#include "BaconBox/Display/Window/ios/BaconBoxAppViewController.h"

namespace BaconBox {
	/**
	 * This is an implementation of MainWindow for IOS.
	 * @ingroup WindowDisplay
	 */
	class IOSMainWindow : public MainWindow {
		friend class MainWindow;
		BB_SINGLETON_DECL(IOSMainWindow);
	public:
		void onBaconBoxInit(unsigned int resolutionWidth, unsigned int resolutionHeight, float contextWidth, float contextHeight, WindowOrientation::type orientation);
		void show();
		void setCaption(const std::string &caption);
		bool isFullScreen() const;
		void setFullScreen(bool);
		
		
		void setUpdatesPerSecond(double updatesPerSecond);
		
//		void setOrientation(WindowOrientation::type newOrientation);

		/**
		 * Checks if the main window grabs the input. Whenà the input is
		 * grabbed, the cursor is invisible.
		 * @return True if the main window grabbed the input, false if not.
		 */
		bool isInputGrabbed() const;

		/**
		 * Sets if the main window grabbed the input or not.
		 * @param newInputGrabbed
		 */
		void setInputGrabbed(bool newInputGrabbed);
		/**
		 * Set the resolution of the window.
		 */
		void setResolution(unsigned int resolutionWidth, unsigned int resolutionHeight);
		void setContextSize(float newContextWidth, float newContextHeight);
//		WindowOrientation::type getOrientation() const;
	private:
		BaconBoxAppViewController *viewController;
		IOSMainWindow();

		~IOSMainWindow();
	};
}

#endif
