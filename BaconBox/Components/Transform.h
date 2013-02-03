#ifndef BB_TRANSFORM_H
#define BB_TRANSFORM_H

#include "BaconBox/Core/Component.h"
#include "BaconBox/Vector2.h"
#include "BaconBox/Core/Entity.h"
#include "BaconBox/Input/Pointer/Pointer.h"

namespace BaconBox {
	class Transform : public Component {
	public:
		BB_ID_HEADER;
		
		
		static const int MESSAGE_GET_POSITION = 0;
		static const int MESSAGE_GET_ROTATION = 1;
		static const int MESSAGE_GET_SCALE = 2;
		static const int MESSAGE_SET_POSITION = 3;
		static const int MESSAGE_SET_ROTATION = 4;
		static const int MESSAGE_SET_SCALE = 5;
		static const int MESSAGE_POSITION_CHANGED = 6;
		static const int MESSAGE_ROTATION_CHANGED = 7;
		static const int MESSAGE_SCALE_CHANGED = 8;
		
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
