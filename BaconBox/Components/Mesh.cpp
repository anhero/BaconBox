#include "Mesh.h"
#include "BaconBox/Core/IDManager.h"
#include "BaconBox/Components/Transform.h"
#include "BaconBox/Core/Entity.h"

namespace BaconBox {
	BB_ID_IMPL(Mesh);

	Mesh::Mesh() : Component() {

	}

	StandardVertexArray &Mesh::getVertices() {
		return vertices;
	}

	void Mesh::receiveMessage(int senderID, int destID, int message, void *data) {
		if (senderID == Transform::ID && destID == Entity::BROADCAST) {
			switch (message) {
			case Transform::MESSAGE_POSITION_CHANGED: {
				Vector2 newPosition(*reinterpret_cast<Vector2 *>(data));

				// TODO: change the vertices' position.
				break;
			}

			case Transform::MESSAGE_ROTATION_CHANGED: {
				float newRotation = *reinterpret_cast<float *>(data);

				// TODO: change the vertices' rotation.
				break;
			}

			case Transform::MESSAGE_SCALE_CHANGED: {
				Vector2 newScale(*reinterpret_cast<Vector2 *>(data));

				// TODO: change the vertices' scaling.
				break;
			}

			default:
				break;
			}
		}
	}
}
