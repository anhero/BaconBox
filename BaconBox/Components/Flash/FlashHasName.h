#ifndef BB_FLASHHASNAME_H
#define BB_FLASHHASNAME_H

#include "BaconBox/Components/HasName.h"
#include "MovieClipHolder.h"
namespace BaconBox {
	class FlashHasName : public HasName {
	public:
		
		FlashHasName();
		
		const std::string &getName() const;
		void setName(const std::string &newName);
		
	private:
		MovieClipHolder * movieClipHolder;
		void initializeConnections();
	};
}

#endif
