#include "Mesh.h"
#include "BaconBox/Core/IDManager.h"
#include "BaconBox/Components/Transform.h"
#include "BaconBox/Core/Entity.h"
#include "BaconBox/Helper/Vector2ChangedData.h"
#include "BaconBox/Helper/ValueChangedData.h"

namespace BaconBox {
	BB_ID_IMPL(Mesh);

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

	void Mesh::receiveMessage(int senderID, int destID, int message, void *data) {
		if (senderID == Transform::ID && destID == Entity::BROADCAST) {
			switch (message) {
			case Transform::MESSAGE_POSITION_CHANGED: {
				Vector2ChangedData newPosition(*reinterpret_cast<Vector2ChangedData *>(data));
				
				this->vertices.move(newPosition.newValue.x - newPosition.oldValue.x, newPosition.newValue.y - newPosition.oldValue.y);
				break;
			}

			case Transform::MESSAGE_ROTATION_CHANGED: {
				ValueChangedData<float> newRotation(*reinterpret_cast<ValueChangedData<float> *>(data));

				Transform *transform = reinterpret_cast<Transform*>(this->getEntity()->getComponent(Transform::ID));
				
				if (transform) {
					this->vertices.rotateFromPoint(newRotation.newValue - newRotation.oldValue, transform->getPosition());
				}
				break;
			}

			case Transform::MESSAGE_SCALE_CHANGED: {
				Vector2ChangedData newScale(*reinterpret_cast<Vector2ChangedData *>(data));
				
				Transform *transform = reinterpret_cast<Transform*>(this->getEntity()->getComponent(Transform::ID));
				
				if (transform) {
					this->vertices.scaleFromPoint(newScale.newValue.x / newScale.oldValue.x, newScale.newValue.y / newScale.oldValue.y, transform->getPosition());
				}
				break;
			}

			default:
				break;
			}
		}
	}
}
