/**
 * @file
 */
#ifndef BB_CAMERADRIVERRENDERER_H
#define BB_CAMERADRIVERRENDERER_H

#include "BaconBox/Core/Component.h"
namespace BaconBox {
	class Transform;
	class ColorTransform;
	class Shake;
	
	/**
	 *
	 */
	class CameraDriverRenderer  : public Component {
    public:
		BB_ID_HEADER;

		CameraDriverRenderer();

		CameraDriverRenderer(const CameraDriverRenderer &src);

		virtual ~CameraDriverRenderer();

		CameraDriverRenderer &operator=(const CameraDriverRenderer &src);

		virtual CameraDriverRenderer *clone() const;

		void update();
    private:	
        Transform * transform;
        ColorTransform * colorTransform;
		Shake *shake;
		void initializeConnections();

	};
}

#endif // BB_CAMERADRIVERRENDERER_
