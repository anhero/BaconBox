#ifndef BB_COMPONENT_CONNECTION_H
#define BB_COMPONENT_CONNECTION_H

#include "BaconBox/Components/IComponentConnection.h"
#include "BaconBox/Core/Entity.h"
#include "BaconBox/Components/ComponentAddedData.h"

namespace BaconBox {
	template <typename TComponent>
	class ComponentConnection : public IComponentConnection {
	public:
		ComponentConnection(TComponent **newComponent) : component(newComponent) {
		}
		
		void componentRemoved(int id) {
			if (id == TComponent::ID) {
				*component = NULL;
			}
		}
		
		void componentAdded(const ComponentAddedData &data) {
			if (data.id == TComponent::ID) {
				*component = reinterpret_cast<TComponent *>(data.component);
			}
		}

		void refreshConnection(Entity *parent) {
			*component = reinterpret_cast<TComponent *>(parent->getComponent(TComponent::ID));
		}
	private:
		TComponent ** const component;
	};
}

#endif /* defined(BB_ComponentConnection_H) */

