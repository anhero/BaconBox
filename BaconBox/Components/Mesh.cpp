#include "Mesh.h"
#include "BaconBox/Core/IDManager.h"
namespace BaconBox {
	int Mesh::ID = IDManager::getID();
	Mesh::Mesh() : Component(){
	
	}
	
	StandardVertexArray & Mesh::getVertices(){
		return vertices;
	}
}
