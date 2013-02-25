#ifndef BB_HASNAME_H
#define BB_HASNAME_H

#include "BaconBox/Core/Component.h"
#include <string>
#include "BaconBox/Core/Entity.h"

namespace BaconBox {
	class HasName : public Component {
	public:
		BB_ID_HEADER;
		
		HasName(const std::string & name);
		
		const std::string &getName() const;
		void setName(const std::string &newName);
		
	private:
	    std::string name;
	};
	
	
	class HasNameProxy : public ComponentProxy{
	public:
		HasNameProxy(Entity* entity, const std::string & name = "", bool mustAddComponent = true);
		
		const std::string &getName() const;
		void setName(const std::string &newName);
	private:
		
	};
}

#endif
