#ifndef BB_COMPONENT_CONNECTION_H
#define BB_COMPONENT_CONNECTION_H

#include "BaconBox/Helper/IComponentConnection.h"
#include "BaconBox/Core/Entity.h"

namespace BaconBox {
	template <typename TComponent>
	class ComponentConnection : public IComponentConnection {
	public:
		ComponentConnection(TComponent **newComponent) : component(newComponent) {
		}
		
		void receiveMessage(int message, void *data) {
			if (message == Entity::MESSAGE_ADD_COMPONENT) {
				*component = reinterpret_cast<TComponent *>(data);
			} else if (message == Entity::MESSAGE_REMOVE_COMPONENT) {
				*component = NULL;
			}
		}
	private:
		TComponent ** const component;
	};
}

#endif /* defined(BB_ComponentConnection_H) */

