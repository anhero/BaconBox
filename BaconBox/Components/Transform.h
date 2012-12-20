#ifndef BB_TRANSFORM_H
#define BB_TRANSFORM_H

#include "Component.h"
#include "Vector2.h"

namespace BaconBox {
	class Transform : public Component {
	public:
		static int ID;
		
		static const int MESSAGE_GET_POSITION = 0;
		static const int MESSAGE_GET_ROTATION = 1;
		static const int MESSAGE_GET_SCALE = 2;
		static const int MESSAGE_SET_POSITION = 3;
		static const int MESSAGE_SET_ROTATION = 4;
		static const int MESSAGE_SET_SCALE = 5;
		
		Transform();
		
		Transform(const Transform &src);
		
		virtual ~Transform();
		
		Transform &operator=(const Transform &src);
		
		virtual Transform *clone() const;
		
		virtual int getID() const;
		
		virtual void receiveMessage(int id, int message, void *data);
		
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
}

#endif
