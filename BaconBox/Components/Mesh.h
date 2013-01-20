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
		static int ID;
		Mesh();
		StandardVertexArray &getVertices();
		
		virtual int getID() const;
		
		virtual void receiveMessage(int senderID, int destID, int message, void *data);
    private:
		StandardVertexArray vertices;
	};
}

#endif // BB_MeshComponent_H
