/**
 * @file
 */
#ifndef BB_MeshComponent_H
#define BB_MeshComponent_H
#include <vector>
#include "Vector2.h"
#include "Component.h"
#include "../StandardVertexArray.h"
namespace BaconBox {
	/**
	 * 
	 */
	class Mesh  : public Component {
    public:
		Mesh();
		StandardVertexArray & GetVertices();
        
    private:
		StandardVertexArray vertices;
		
	};
}

#endif // BB_MeshComponent_H