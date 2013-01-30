#ifndef BB_MESH_DRIVER_RENDERER_H
#define BB_MESH_DRIVER_RENDERER_H

#include "BaconBox/Core/Component.h"

namespace BaconBox {
	class Mesh;
	
	class MeshDriverRenderer : public Component {
	public:
		BB_ID_HEADER;
		
		MeshDriverRenderer();
				
		virtual void render();
	private:
		Mesh *mesh;
	};
}

#endif
