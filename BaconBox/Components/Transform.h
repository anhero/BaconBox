#ifndef BB_TRANSFORM_H
#define BB_TRANSFORM_H

#include "BaconBox/Core/Component.h"
#include "BaconBox/Vector2.h"
#include "BaconBox/Core/Entity.h"
#include "BaconBox/Input/Pointer/Pointer.h"
#include "BaconBox/Matrix.h"
#include "BaconBox/Helper/Vector2ChangedData.h"
#include "BaconBox/Property.h"
namespace BaconBox {
	class MatrixComponent;
	class TransformProxy;
	/**
	 * Component that manages the entity's position, orientation and scaling
	 * values.
	 */
	class Transform : public Component {
	public:
		BB_ID_HEADER;
		friend class MatrixComponent;
		friend class TransformProxy;
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
		ç */
		virtual const Vector2 &getPosition() const;
		

		virtual const Vector2 &getRealPosition();

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
		
#ifdef SWIG
		float x;
		float y;
		float scaleX;
		float scaleY;
		float rotation;
#else
		Property<float, Transform> x;
		Property<float, Transform> y;
		Property<float, Transform> scaleX;
		Property<float, Transform> scaleY;
		Property<float, Transform> rotation;
#endif

	protected:
		void initializeConnections();
		
		void setRotationInternal(float rotation);
		
		void setX(float X);
		void setY(float X);
		void setScaleX(float X);
		void setScaleY(float X);
		
		float getX() const;
		float getY() const;
		float getScaleX() const;
		float getScaleY() const;
		

		Vector2 _position;

		Vector2 realPosition;

		/**
		 * Entity's rotation angle (in degrees, from -180 to 180).
		 */
		float _rotation;

		/**
		 * Entity's horizontal and vertical scale values.
		 */
		Vector2 _scale;

	private:
		MatrixComponent *matrixComponent;
	};

	class TransformProxy : public ComponentProxy {
	public:
		TransformProxy(Entity *entity, bool mustAddComponent = true);

		const Vector2 &getPosition() const;
		void setPosition(const Vector2 &newPosition);
		
		float getXPosition() const;
		float getYPosition() const;
		
		void setXPosition(float newXPosition);
		void setYPosition(float newYPosition);

		const Vector2 &getRealPosition() const;

		float getRotation() const;
		void setRotation(float newRotation);

		const Vector2 &getScale() const;
		void setScale(const Vector2 &newScale);
#ifdef SWIG
		float  x;
		float  y;
		float  scaleX;
		float  scaleY;
		float  rotation;
#else
		Property<float, Transform> x;
		Property<float, Transform> y;
		Property<float, Transform> scaleX;
		Property<float, Transform> scaleY;
		Property<float, Transform> rotation;
#endif
	protected:
		void setTransform(Transform *transform);
		void setProperties(Transform *transform);
	};
}

#endif
