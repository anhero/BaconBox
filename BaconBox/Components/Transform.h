#ifndef BB_TRANSFORM_H
#define BB_TRANSFORM_H

#include "BaconBox/Core/Component.h"
#include "BaconBox/Vector2.h"
#include "BaconBox/Core/Entity.h"
#include "BaconBox/Input/Pointer/Pointer.h"

namespace BaconBox {
	/**
	 * Component that manages the entity's position, orientation and scaling
	 * values.
	 */
	class Transform : public Component {
	public:
		BB_ID_HEADER;
		
		/// Message ID to use when requesting the entity's position.
		static int MESSAGE_GET_POSITION;
		/// Message ID to use when requesting the entity's rotation angle.
		static int MESSAGE_GET_ROTATION;
		/// Message ID to use when requesting the entity's scale values.
		static int MESSAGE_GET_SCALE;
		/// Message ID to use when setting the entity's position.
		static int MESSAGE_SET_POSITION;
		/// Message ID to use when setting the entity's rotation angle.
		static int MESSAGE_SET_ROTATION;
		/// Message ID to use when setting the entity's scale values.
		static int MESSAGE_SET_SCALE;
		/// Message ID the component sends when its entity's position has changed.
		static int MESSAGE_POSITION_CHANGED;
		/// Message ID the component sends when its entity's rotation angle has changed.
		static int MESSAGE_ROTATION_CHANGED;
		/// Message ID the component sends when its entity's scale values have changed.
		static int MESSAGE_SCALE_CHANGED;
		
		Transform();
		
		Transform(const Transform &src);
		
		virtual ~Transform();
		
		Transform &operator=(const Transform &src);
		
		virtual Transform *clone() const;
		
		virtual void receiveMessage(int senderID, int destID, int message, void *data);
		
		const Vector2 &getPosition() const;
		void setPosition(const Vector2 &newPosition);
		
		float getRotation() const;
		void setRotation(float newRotation);
		
		const Vector2 &getScale() const;
		void setScale(const Vector2 &newScale);
		
	private:
		/**
		 * Entity's position. All rotations and scaling are applied from this
		 * point.
		 */
		Vector2 position;
		float rotation;
		Vector2 scale;
	};
	
	
	class TransformProxy : public ComponentProxy {
	public:
		TransformProxy(Entity* entity, bool mustAddComponent = true);
		
		const Vector2 &getPosition() const;
		void setPosition(const Vector2 &newPosition);
		
		float getRotation() const;
		void setRotation(float newRotation);
		
		const Vector2 &getScale() const;
		void setScale(const Vector2 &newScale);
		
		
	private:

	};
}

#endif
