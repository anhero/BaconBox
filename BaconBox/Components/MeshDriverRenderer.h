#ifndef BB_MESH_DRIVER_RENDERER_H
#define BB_MESH_DRIVER_RENDERER_H

#include "BaconBox/Core/Component.h"
#include "BaconBox/Display/RenderMode.h"

namespace BaconBox {
	class Mesh;
	class Texture;
	class ColorFilter;
	class Visibility;

	class MeshDriverRenderer : public Component {
	public:
		BB_ID_HEADER;
		
		static int MESSAGE_GET_RENDER_MODE;
		static int MESSAGE_SET_RENDER_MODE;
		
		MeshDriverRenderer(int newRenderMode = (RenderMode::SHAPE | RenderMode::COLOR));
		
		MeshDriverRenderer(const MeshDriverRenderer &src);
		
		virtual ~MeshDriverRenderer();
				
		MeshDriverRenderer &operator=(const MeshDriverRenderer &src);
		
		virtual MeshDriverRenderer *clone() const;
		
		virtual void receiveMessage(int senderID, int destID, int message, void *data);
		
		virtual void render();
		
		int getRenderMode() const;
		
		void setRenderMode(int newRenderMode);
	private:
		void initializeConnections();
		
		Mesh *mesh;
		Texture *texture;
		ColorFilter *colorFilter;
		Visibility *visibility;

		int renderMode;
	};
}

#endif
