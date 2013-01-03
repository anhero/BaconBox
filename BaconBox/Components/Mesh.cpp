#include "Mesh.h"

namespace BaconBox {
	Mesh::Mesh() : Component(){
	
	}
	
	StandardVertexArray & Mesh::GetVertices(){
		return vertices;
	}
}