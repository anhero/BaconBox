#ifndef BB_COMPONENT_H
#define BB_COMPONENT_H

#include <string>
#include "BaconBox/Core/IDManager.h"

namespace BaconBox {
	class Entity;
	
	class Component {
		friend class Entity;
	public:
		BB_ID_HEADER;
		
		Component();
		
		Component(const Component &src);
		
		virtual ~Component();
		
		Component &operator=(const Component &src);
		
		virtual Component *clone() const;
				
		void sendMessage(int destID, int message, void *data);
		virtual void receiveMessage(int senderID, int destID, int message, void *data);
		
		virtual void update();
		virtual void render();
		
		const std::string &getName() const;
		void setName(const std::string& newName);
		
		Entity *getEntity() const;
	private:
		std::string name;
		Entity *entity;
	};
}

#endif
