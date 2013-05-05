#ifndef BB_TRANSFORM_H
#define BB_TRANSFORM_H

#include "BaconBox/Core/Component.h"
#include "BaconBox/Vector2.h"
#include "BaconBox/Core/Entity.h"
#include "BaconBox/Input/Pointer/Pointer.h"
#include "BaconBox/Matrix.h"
#include "BaconBox/Helper/Vector2ChangedData.h"
namespace BaconBox {
	class MatrixComponent;
	/**
	 * Component that manages the entity's position, orientation and scaling
	 * values.
	 */
	class Transform : public Component {
	public:
		BB_ID_HEADER;
		friend class MatrixComponent;
		

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
		
		

		/**
		 * Default constructor.
		 */
		Transform();

		/**
		 * Copy constructor.
		 * @param src Transform component to create a copy of.
		 */
		Transform(const Transform &src);

		/**
		 * Destructor.
		 */
		virtual ~Transform();

		/**
		 * Assignment operator overload.
		 * @param src Transform component to copy.
		 * @return Reference to the current instance.
		 */
		Transform &operator=(const Transform &src);

		/**
		 * Clones the current instance.
		 */
		virtual Transform *clone() const;

		/**
		 * Handles the messages received.
		 * @param senderID Type ID of component/entity sending the message.
		 * @param destID Type ID of the component/entity the message is
		 * destined to.
		 * @param data Data used to send or receive any data related to the
		 * message.
		 */
		virtual void receiveMessage(int senderID, int destID, int message, void *data);

		/**
		 * Gets the entity's position.
		 * @return Vector2 containing the entity's position.
		 * @see BaconBox::Transform::position
		 */
		const Vector2 &getPosition() const;
		
		/**
		 * Sets the entity's position.
		 * @param newPosition Vector2 containing the entity's new position.
		 */
		void setPosition(const Vector2 &newPosition, bool withMessage = true);

		/**
		 * Gets the entity's rotation angle.
		 */
		float getRotation() const;
		/**
		 * Sets the entity's rotation angle.
		 * @param newRotation New rotation angle.
		 */
		void setRotation(float newRotation, bool withMessage = true);

		/**
		 * Gets the entity's scale values.
		 * @return Entity's current scale values.
		 */
		const Vector2 &getScale() const;
		
		/**
		 * Sets the entity's scale values.
		 * @param newScale Vector2 containing the entity's new scale values.
		 */
		void setScale(const Vector2 &newScale, bool withMessage = true);
	

		
	private:
	    

		    
	    	/**
		 * Entity's position. All rotations and scaling are applied from this
		 * point.
		 */
		Vector2 position;
		
		/**
		 * Entity's rotation angle (in degrees, from -180 to 180).
		 */
		float rotation;
		
		/**
		 * Entity's horizontal and vertical scale values.
		 */
		Vector2 scale;
		
	};


	class TransformProxy : public ComponentProxy {
	public:
		TransformProxy(Entity *entity, bool mustAddComponent = true);
		


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
