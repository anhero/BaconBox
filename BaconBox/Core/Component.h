#ifndef BB_COMPONENT_H
#define BB_COMPONENT_H

#include <string>
#include <vector>
#include "BaconBox/Core/IDManager.h"

#include <sigly.h>


//To use this macro, your Proxy must take these two parameters NAMES ARE IMPORTANT (Entity* entity, bool mustAddComponent)
#define BB_PROXY_CONSTRUCTOR(componentConstructor) ComponentProxy(entity, (mustAddComponent ? componentConstructor : NULL))



namespace BaconBox {
	class Entity;
	class IComponentConnection;
	
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
		
		const std::string &getComponentName() const;
		
		Entity *getEntity() const;
	protected:
		void addConnection(IComponentConnection *newConnection);
		
		virtual void updateConnections();
	private:
		void setEntity(Entity *newEntity);
		
		Entity *entity;
		
		std::vector<IComponentConnection *> connections;
	};
	
	
	class ComponentProxy {
	protected:
	    ComponentProxy(Entity* entity, Component * component);
	    Component * component;
	    Entity* entity;
	};
}

#endif
