#include "FlashHasName.h"
#include "BaconBox/Components/ComponentConnection.h"

#include <AS3/AS3.h>
#include <AS3/AS3++.h>
namespace BaconBox {
	
	 
	 FlashHasName::FlashHasName():HasName(""){
	    initializeConnections();
	 }

	 void FlashHasName::initializeConnections(){
	    this->addConnection(new ComponentConnection<MovieClipHolder>(&this->movieClipHolder));
	}

	const std::string &FlashHasName::getName() const {
		AS3::local::var tempName = movieClipHolder->getProperty("name");
		const_cast<FlashHasName*>(this)->name = AS3::sz2stringAndFree(AS3::local::internal::utf8_toString(tempName));
		return name;
	}

	void FlashHasName::setName(const std::string &newName) {
		name = newName;
		movieClipHolder->setProperty("name",  AS3::local::internal::new_String(newName.c_str()));
	}
	
}