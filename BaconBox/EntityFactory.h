#ifndef BB_ENTITY_FACTORY_H
#define BB_ENTITY_FACTORY_H

#include "BaconBox/Core/Entity.h"
namespace BaconBox {

	class EntityFactory {
	public:
	    EntityFactory();
	    Entity * getEntity(std::string & key);
	private:
		
	};

}

#endif
