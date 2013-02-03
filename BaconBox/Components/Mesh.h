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
	 * 
	 */
	class Mesh  : public Component {
    public:
		BB_ID_HEADER;
		
		Mesh();
		
		StandardVertexArray &getVertices();
		
		/**
		 * Gets the vertices relative to the entity's position.
		 * @return Array of vertices with their positions relative to the 
		 * entity's position.
		 */
		const StandardVertexArray getRelativeVertices() const;
		
		void move(const Vector2 &delta);
		
		virtual void receiveMessage(int senderID, int destID, int message, void *data);
    private:
		StandardVertexArray vertices;
	};
}

#endif // BB_MeshComponent_H
