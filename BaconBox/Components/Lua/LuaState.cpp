#include "LuaState.h"

#include "BaconBox/Core/Entity.h"

#include "lua.hpp"
#include <iostream>

namespace BaconBox {
	 BB_ID_IMPL(LuaState);
	
	LuaState::LuaState() : Component() {
		setName("LuaState");
	}


	void LuaState::setLuaClass(lua_State * L){
		std::cout << L << std::endl;

	}

	void LuaState::receiveMessage(int senderID, int destID, int message, void *data) {
            //if(destID != LuaState::ID)return;
	}
}