/**
 * @file
 * @ingroup WindowDisplay
 */
#ifndef BB_ANDROID_MAIN_WINDOW_H
#define BB_ANDROID_MAIN_WINDOW_H


#include "BaconBox/Display/Window/MainWindow.h"


 #include <EGL/egl.h>

struct android_app;

namespace BaconBox {
	

	class AndroidMainWindow : public MainWindow {
		friend class MainWindow;
		BB_SINGLETON_DECL(AndroidMainWindow);
	public:
	void onBaconBoxInit(unsigned int resolutionWidth,
			                  unsigned int resolutionHeight,
			                  float contextWidth,
			                  float contextHeight,
								WindowOrientation::type orientation);

		void setUpdatesPerSecond(double setFrameInterval);


		/**
		 * Activates and opens the window.
		 */
		void show();

		/**
		 * Changes the caption of the window. This is usually
		 * the title in the titlebar.
		 * @param caption The text used to replace the title.
		 */
		void setCaption(const std::string &caption);

		/**
		 * Checks if the main window is full screen.
		 * @return True if the main window is in full screen, false if not.
		 */
		bool isFullScreen() const;

		/**
		 * Makes the main window full screen or not.
		 * @param newFullScreen If true, sets the main window to full screen.
		 * If false, makes sure it's not full screen.
		 */
		void setFullScreen(bool newFullScreen);

		/**
		 * Checks if the main window grabs the input. When the input is
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
        
        /**
         * Hide the pointer. The pointer still work, but it won't be visible.
         */
        void hideCursor();
        
        /**
         * Show the pointer. If you called hideCursor(), this will reactivate it.
         */
        void showCursor();


		/**
		 * Sets the context size. If you want to work in pixels, set them to 0 and they
		 * will automagically match the current resolution width and height
		 */
		void setContextSize(float newContextWidth,
		                    float newContextHeight);

		static void handleCmd(struct android_app* app, int32_t cmd);

		static void loop();

		void handleResize();

	protected:
		/**
		 * Inits the properties of the window Android-side, but leaves stuff to be
		 * picked up at object initialization for engine-side stuff.
		 */
		static void deferredInitWindow();
		static bool deferredInitializationDone;
		static EGLDisplay deferredDisplay;
		static EGLSurface deferredSurface;
		static EGLContext deferredContext;

	private:

		void termWindow();
		void initWindow();
		static AndroidMainWindow * androidMainWindow;
	    EGLDisplay display;
	    EGLSurface surface;
	    EGLContext context;
	    bool needContext;
	   	static bool animating;	
	   	bool soundMuted;
	   	bool musicMuted;
		AndroidMainWindow();

	
		~AndroidMainWindow();
	};
}

#endif
