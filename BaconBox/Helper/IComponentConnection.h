#ifndef BB_ICOMPONENT_DEFINITION_H
#define BB_ICOMPONENT_DEFINITION_H

namespace BaconBox {
	class IComponentConnection {
	public:
		virtual void receiveMessage(int message, void *data) = 0;
	};
}

#endif
