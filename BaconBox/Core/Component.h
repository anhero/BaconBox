#ifndef BB_COMPONENT_H
#define BB_COMPONENT_H

#include <string>

#include "ID.h"

namespace BaconBox {
	class Entity;
	
	class Component {
		friend class Entity;
	public:
		HAS_ID(Component);
		
		void sendMessage(int message, void *data);
		virtual void receiveMessage(int id, int message, void *data);
		
		virtual void update();
		virtual void render();
		
		const std::string &getName() const;
		void setName(const std::string& newName);
	private:
		std::string name;
		Entity *entity;
	};
}

#endif
