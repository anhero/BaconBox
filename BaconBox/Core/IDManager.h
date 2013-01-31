#ifndef BB_ID_MANAGER_H
#define BB_ID_MANAGER_H


#define BB_ID_HEADER \
static int ID; \
virtual int getID() const

#define BB_ID_IMPL(ClassName) \
int ClassName::getID() const {		\
	return ClassName::ID;		\
}					\
int ClassName::ID = IDManager::getID()

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
