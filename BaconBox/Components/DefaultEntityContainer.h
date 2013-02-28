#ifndef BB_DefaultEntityContainer_H
#define BB_DefaultEntityContainer_H

#include "BaconBox/Core/Component.h"

namespace BaconBox {
	class DefaultEntityContainer : public Component {
	public:
		BB_ID_HEADER;
		
		DefaultEntityContainer();
		
		DefaultEntityContainer(const DefaultEntityContainer &src);
		
		virtual ~DefaultEntityContainer();
		
		DefaultEntityContainer &operator=(const DefaultEntityContainer &src);
		
		virtual DefaultEntityContainer *clone() const;
		
		virtual void receiveMessage(int senderID, int destID, int message, void *data);
	private:
	};
}

#endif /* defined(BB_DefaultEntityContainer_H) */

