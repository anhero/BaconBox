/**
 * @file
 */
#ifndef BB_CAMERADRIVERRENDERER_H
#define BB_CAMERADRIVERRENDERER_H

#include "BaconBox/Core/Component.h"
#include "BaconBox/Components/Transform.h"
#include "BaconBox/Components/ColorTransform.h"
namespace BaconBox {
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

		void render();
    private:	
        Transform * transform;
        ColorTransform * colorTransform;
		void initializeConnections();

	};
}

#endif // BB_CAMERADRIVERRENDERER_
