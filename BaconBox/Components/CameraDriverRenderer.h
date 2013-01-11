/**
 * @file
 */
#ifndef BB_CAMERADRIVERRENDERER_H
#define BB_CAMERADRIVERRENDERER_H

#include "BaconBox/Core/Component.h"


namespace BaconBox {
	/**
	 * 
	 */
	class CameraDriverRenderer  : public Component {
    public:
		static int ID;
		
		CameraDriverRenderer();
		
		CameraDriverRenderer(const CameraDriverRenderer &src);
		
		virtual ~CameraDriverRenderer();
		
		CameraDriverRenderer &operator=(const CameraDriverRenderer &src);
		
		virtual CameraDriverRenderer *clone() const;
		
		virtual int getID() const;
		
		virtual void receiveMessage(int id, int message, void *data);
		
		virtual void update();
		
		virtual void render();
    private:
        
	};
}

#endif // BB_CAMERADRIVERRENDERER_
