#include "Mesh.h"
#include "BaconBox/Core/IDManager.h"
#include "BaconBox/Components/Transform.h"
#include "BaconBox/Core/Entity.h"
#include "BaconBox/Helper/Vector2ChangedData.h"

namespace BaconBox {
	int Mesh::ID = IDManager::getID();

	Mesh::Mesh() : Component() {

	}

	StandardVertexArray &Mesh::getVertices() {
		return vertices;
	}
	
	const StandardVertexArray Mesh::getRelativeVertices() const {
		Transform *transform = reinterpret_cast<Transform*>(this->getEntity()->getComponent(Transform::ID));
		
		if (transform) {
			StandardVertexArray result(this->vertices);
			
			Vector2 position = transform->getPosition();
			
			result.move(-position.x, -position.y);
			
			return result;
		} else {
			return StandardVertexArray();
		}
	}

	int Mesh::getID() const {
		return Mesh::ID;
	}

	void Mesh::receiveMessage(int senderID, int destID, int message, void *data) {
		if (senderID == Transform::ID && destID == Entity::BROADCAST) {
			switch (message) {
			case Transform::MESSAGE_POSITION_CHANGED: {
				Vector2ChangedData newPosition(*reinterpret_cast<Vector2ChangedData *>(data));

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
