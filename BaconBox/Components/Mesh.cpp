#include "Mesh.h"

namespace BaconBox {
	Mesh::Mesh() : Component(){
	
	}
	
	StandardVertexArray & Mesh::getVertices(){
		return vertices;
	}
}