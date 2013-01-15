/**
 * @file
 */
#ifndef BB_MeshComponent_H
#define BB_MeshComponent_H
#include <vector>
#include "BaconBox/Vector2.h"
#include "BaconBox/Core/Component.h"
#include "../StandardVertexArray.h"
namespace BaconBox {
	/**
	 * 
	 */
	class Mesh  : public Component {
    public:
		Mesh();
		StandardVertexArray & getVertices();
        
    private:
		StandardVertexArray vertices;
		
	};
}

#endif // BB_MeshComponent_H
