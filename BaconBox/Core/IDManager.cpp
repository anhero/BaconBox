#include "IDManager.h"
#include "BaconBox/Console.h"
namespace BaconBox {
	IDManager &IDManager::getInstance() {
		static IDManager instance;
		return instance;
	}
	
	int IDManager::generateID() {
	    return getInstance().counter++;
	}
	
	int IDManager::generateID(const std::string & name) {
	    int id = getInstance().counter++;
	    getInstance().ids[name] = id;
	    return id;
	}

	int IDManager::getID(const std::string & name){
	    std::map<std::string, int>::iterator i = getInstance().ids.find(name);
	    if (i != getInstance().ids.end()){
		return i->second;
	    }
	    else{
		Console__error("Can't find the id associated with this name: " << name);
		return -1;
	    }
	}
	
	const std::string &IDManager::getName(int id){
		for(std::map<std::string, int>::iterator i = getInstance().ids.begin(); i !=getInstance().ids.end(); i++){
			if(i->second == id){
				 return i->first;
			}
		}
		Console__error("Can't find the name associated with this id: " << id);
		
		 static std::string EMPTY; 
		 return EMPTY; 
	}
		
	IDManager::IDManager() : counter(0) {
	}
}
