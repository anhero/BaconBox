/**
 * @file
 */
#ifndef BB_CAMERA_H
#define BB_CAMERA_H


#include "BaconBox/Core/Entity.h"


namespace BaconBox {
	/**
	 * Represents a camera. Its position determines what the player sees on his
	 * screen.
	 */
	class Camera  : public Entity {
    public:
		Camera();
		
		Camera(const Camera &src);
		
		virtual ~Camera();
		
		Camera &operator=(const Camera &src);
		
		virtual Camera *clone() const;
    private:
        
	};
}

#endif // BB_CAMERA_H