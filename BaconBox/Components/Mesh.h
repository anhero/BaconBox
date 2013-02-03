/**
 * @file
 */
#ifndef BB_MeshComponent_H
#define BB_MeshComponent_H
#include <vector>
#include "BaconBox/Vector2.h"
#include "BaconBox/Core/Component.h"
#include "BaconBox/StandardVertexArray.h"

namespace BaconBox {
	/**
	 * Contains the entity's vertices.
	 */
	class Mesh  : public Component {
    public:
		BB_ID_HEADER;
		
		Mesh();
		
		/**
		 * Gets the vertices defining the shape of the mesh.
		 * @return Array of vertices defining the shape of the mesh.
		 */
		StandardVertexArray &getVertices();
		
		/**
		 * Gets the vertices relative to the entity's position.
		 * @return Array of vertices with their positions relative to the 
		 * entity's position.
		 */
		const StandardVertexArray getRelativeVertices() const;
		
		virtual void receiveMessage(int senderID, int destID, int message, void *data);
    private:
		/// Vertices defining the shape of the mesh.
		StandardVertexArray vertices;
	};
}

#endif // BB_MeshComponent_H
