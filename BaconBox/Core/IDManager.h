#ifndef BB_ID_MANAGER_H
#define BB_ID_MANAGER_H

namespace BaconBox {
	class IDManager {
	public:
		static int getID();
	private:
		static IDManager &getInstance();
		
		IDManager();
		
		int counter;
	};
}

#endif
