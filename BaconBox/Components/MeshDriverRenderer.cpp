#include "MeshDriverRenderer.h"

#include "BaconBox/Core/IDManager.h"
#include "BaconBox/Components/Mesh.h"
#include "BaconBox/Core/Entity.h"
#include "BaconBox/Display/Driver/GraphicDriver.h"
#include "BaconBox/Core/Engine.h"

namespace BaconBox {
	BB_ID_IMPL(MeshDriverRenderer);

	MeshDriverRenderer::MeshDriverRenderer() : Component(), mesh(NULL) {
	}

	void MeshDriverRenderer::render() {
		if (this->mesh == NULL && this->getEntity()) {
			this->mesh = reinterpret_cast<Mesh *>(this->getEntity()->getComponent(Mesh::ID));
		}
		
		if (this->mesh != NULL) {
			
		}
	}
}
