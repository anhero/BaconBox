#ifndef BB_COMPONENT_H
#define BB_COMPONENT_H

#include <string>
#include "BaconBox/Core/IDManager.h"

#include <sigly.h>


//To use this macro, your Proxy must take these two parameters NAMES ARE IMPORTANT (Entity* entity, bool mustAddComponent)
#define BB_PROXY_CONSTRUCTOR(componentConstructor) ComponentProxy(entity, (mustAddComponent ? componentConstructor : NULL))



namespace BaconBox {
	class Entity;
	
	class Component : public sigly::HasSlots<> {
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
		
		std::string getComponentName() const;
		
		
		Entity *getEntity() const;
	private:
		Entity *entity;
	};
	
	
	class ComponentProxy {
	protected:
	    ComponentProxy(Entity* entity, Component * component);
	    Component * component;
	    Entity* entity;
	};
}

#endif
