#ifndef BB_ID_MANAGER_H
#define BB_ID_MANAGER_H

#include <string>
#include <map>
#define BB_ID_HEADER \
static int ID; \
virtual int getID() const

#define BB_ID_IMPL(ClassName) \
int ClassName::getID() const {		\
	return ClassName::ID;		\
}					\
int ClassName::ID = IDManager::generatetID(#ClassName)

namespace BaconBox {
	class IDManager {
	public:
		static int generatetID();
		static int generatetID(const std::string & name);
		static int getID(const std::string & name);
		static const std::string &getName(int id);
	private:
		static IDManager &getInstance();
		
		IDManager();
		
		int counter;
		
		std::map<std::string, int> ids; 
	};
}

#endif
