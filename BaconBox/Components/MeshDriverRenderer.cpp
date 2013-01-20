#include "MeshDriverRenderer.h"

#include "BaconBox/Core/IDManager.h"
#include "BaconBox/Components/Mesh.h"
#include "BaconBox/Core/Entity.h"
#include "BaconBox/Display/Driver/GraphicDriver.h"
#include "BaconBox/Core/Engine.h"

namespace BaconBox {
	int MeshDriverRenderer::ID = IDManager::getID();

	MeshDriverRenderer::MeshDriverRenderer() : Component(), mesh(NULL) {
	}

	int MeshDriverRenderer::getID() const {
		return MeshDriverRenderer::ID;
	}

	void MeshDriverRenderer::render() {
		if (this->mesh == NULL && this->getEntity()) {
			this->mesh = reinterpret_cast<Mesh *>(this->getEntity()->getComponent(Mesh::ID));
		}
		
		if (this->mesh != NULL) {
		}
	}
}
