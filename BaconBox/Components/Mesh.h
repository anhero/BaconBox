/**
 * @file
 */
#ifndef BB_MeshComponent_H
#define BB_MeshComponent_H
#include <vector>
#include "BaconBox/Vector2.h"
#include "BaconBox/Core/Component.h"
#include "BaconBox/StandardVertexArray.h"
#include "BaconBox/Components/Transform.h"
#include "MatrixComponent.h"

namespace BaconBox {
	/**
	 * Contains the entity's vertices.
	 */
	class Mesh  : public Component {
    public:
		BB_ID_HEADER;
		
		Mesh();
		
		
		StandardVertexArray &getPreTransformVertices();
		StandardVertexArray &getPostTransformVertices();
		void syncMesh();
	
//		const StandardVertexArray getRelativeVertices() const;
		
		virtual void receiveMessage(int senderID, int destID, int message, void *data);
    private:
		/// Vertices defining the shape of the mesh.
		StandardVertexArray postTransformVertices;
		StandardVertexArray preTransformVertices;
		bool mustSync;
		
		void initializeConnections();

		Transform * transform;
		MatrixComponent * matrixComponent;
		
	};
}

#endif // BB_MeshComponent_H
